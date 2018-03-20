#include "robot.h"

inline float wrapAngle( float angle )
{
    double twoPi = 2.0 * PI;
    return angle - twoPi * floor( angle / twoPi );
}
inline float max(float x, float y){
    if(x>y)return x;
    return y;
}

Robot::Robot() :
    right(FEHMotor::Motor0, 7.2), top(FEHMotor::Motor1, 7.2),
    left(FEHMotor::Motor2, 7.2), bottom(FEHMotor::Motor3, 7.2),
    killswitch(KILLSWITCH_PIN), cds(CDS_PIN), kill(false),
    wrench(FEHServo::Servo0)
{
    RPS.InitializeTouchMenu();
    currentLocation = {RPS.X(),RPS.Y()};
    currentAngle = RPS.Heading() * PI / 180;
    wrench.SetMin(SERVO_MIN);
    wrench.SetMax(SERVO_MAX);
    if(DEBUG) {
        SD.OpenLog();
        //SD.Printf("Time, X, Y, Angle, Vx, Vy, estX, estY, travel angle\n");
    }
}

void Robot::moveToPosition(Point pos, float percent, bool slowDown) {
    if(kill)return;
    float distY = pos.y - currentLocation.y, distX = pos.x - currentLocation.x;
    float angle = atan2(distY, distX);
    float distSq = (distY*distY+distX*distX);
    angle -= currentAngle;
    angle = wrapAngle(angle);
    if(DEBUG){
        SD.Printf("%f\n", angle+currentAngle);
    }
    float percentNew = percent;
    if(distSq < POS2*POS2 && slowDown){
        percentNew = distSq/(POS2*POS2);
        percentNew = max(LOWEST, percentNew);
        percentNew *= percent;
    }
    //moves at percent if distance is greater than POS2, else moves at slower speed as it gets closer
    moveAtAngle(angle, percentNew);
}

void Robot::moveAtAngle(float angle, float percent) {
    if(kill)return;
    float vRight = percent* cos(angle);
    float vUp = percent* sin(angle);
    setMotor(TOP, vRight);
    setMotor(BOTTOM, vRight);
    setMotor(RIGHT, vUp);
    setMotor(LEFT, vUp);
}
void Robot::stopAll() {
    stop(TOP);
    stop(BOTTOM);
    stop(RIGHT);
    stop(LEFT);
}
void Robot::turn(float angle, float percent, bool slowDown) {
    if(kill)return;
    float angleDiff = currentAngle-angle;
    bool pos = (angleDiff < 0 && -angleDiff < 3.1415) ||
            (angleDiff > 0 && angleDiff > 3.1415);
    int sign = pos * 2 - 1;
    //slows down if within ANGLE2 radians of desired angle
    float percentNew = percent;
    if(abs(angleDiff) < ANGLE2 && slowDown){
        percentNew = abs(angleDiff)/ANGLE2;
        percentNew = max(LOWEST, percentNew);
        percentNew *= percent;
    }
    setMotor(RIGHT, sign * percentNew);
    setMotor(LEFT, -sign * percentNew);
    setMotor(TOP, -sign * percentNew);
    setMotor(BOTTOM, sign * percentNew);
}

void Robot::updateLocation() {
    if(kill)return;
    Point locationPrev = currentLocation;
    currentLocation.x = RPS.X();
    currentLocation.y = RPS.Y();
    if(currentLocation.x == -1 || currentLocation.y == -1) {
        waitFor(0.1);
        updateLocation();
        return;
    }
    float dt = TimeNow() - lastTime;
    float anglePrev = currentAngle;
    velocity.x = currentLocation.x - locationPrev.x;
    velocity.x /= dt;
    velocity.y = currentLocation.y - locationPrev.y;
    velocity.y /= dt;
    currentAngle = RPS.Heading() * PI / 180 + OFFSET_ANGLE;
    currentAngle = fmod(currentAngle, 2*PI);
    angularV = currentAngle - anglePrev;
    angularV /= dt;
    lastTime = TimeNow();
    if(DEBUG) {
        SD.Printf("%f, %f, %f, %f, %f, %f, ", TimeNow(),
                  currentLocation.x, currentLocation.y, currentAngle, velocity.x, velocity.y);
    }
}
void Robot::setMotor(Motors m, float percent) {
    if(kill)return;
    switch(m) {
    case RIGHT:
        right.SetPercent(percent);
        break;
    case TOP:
        top.SetPercent(percent);
        break;
    case BOTTOM:
        bottom.SetPercent(percent);
        break;
    case LEFT:
        left.SetPercent(1.35*percent);
        break;
    }
}
void Robot::stop(Motors m) {
    switch(m) {
    case RIGHT:
        right.Stop();
        break;
    case TOP:
        top.Stop();
        break;
    case BOTTOM:
        bottom.Stop();
        break;
    case LEFT:
        left.Stop();
        break;
    }
}

/*
 * Waits until the robot is within POSITION_TOLERANCE inches of location.
 */
void Robot::waitMoveToLocation(Point location, float percent, bool slowDown) {
    LCD.Clear();
    float estX = currentLocation.x, estY = currentLocation.y;
    while(!kill
            && (abs(estX - location.x) > POSITION_TOLERANCE
            || abs(estY - location.y) > POSITION_TOLERANCE)) {

        waitFor(0.1);

        if(!killswitch.Value())kill = true;
        updateLocation();
        estX = currentLocation.x + velocity.x * OFFSET_TIME;
        estY = currentLocation.y + velocity.y * OFFSET_TIME;
        if(DEBUG) {
            SD.Printf("%f, %f, ", estX, estY);
            LCD.WriteRC("Location: ", 0, 0);
            LCD.WriteRC(currentLocation.x, 0, 10);
            LCD.WriteRC(currentLocation.y, 0, 20);
            LCD.WriteRC("Angle: ", 1, 0);
            LCD.WriteRC(currentAngle, 1, 10);
            LCD.WriteRC("Velocity:", 2, 0);
            LCD.WriteRC(velocity.x, 2, 10);
            LCD.WriteRC(velocity.y, 2, 20);
            LCD.WriteRC("Est loc:", 3, 0);
            LCD.WriteRC(estX, 3, 10);
            LCD.WriteRC(estY, 3, 20);
        }
        moveToPosition(location, percent, slowDown);
    }
    LCD.WriteRC("At ", 4, 0);
    LCD.WriteRC(location.x, 4, 10);
    LCD.WriteRC(location.y, 4, 20);
    stopAll();
}

/*
 * Waits until the robot is within ANGLE_TOLERANCE of angle.
 */
void Robot::waitMoveToAngle(float angle, float power, bool slowDown) {
    float estAngle = currentAngle;
    turn(angle, power, slowDown);
    while(!kill && abs(estAngle - angle) > ANGLE_TOLERANCE) {
        if(!killswitch.Value())kill = true;
        waitFor(0.1);
        updateLocation();
        turn(angle, power, slowDown);
        estAngle = currentAngle + angularV * OFFSET_TIME;
    }
    stopAll();
}
/*
 * Waits for the analog input pin to be less than or greater than the given threshold.
 * Also listens for the killswitch.
 * (pin.Value() < threshold) != lessThan    <--   True if they're both true or both false
 *
 * pin:  The pin to listen for
 * threshold: The threshold to cross
 * lessThan:  If it's  true, returns when pin is  less than threshold, otherwise
 *              returns when pin is greater than threshold.
 */
void Robot::waitForPin(AnalogInputPin pin, float threshold, bool lessThan) {
    while(!kill && ((pin.Value() < threshold) != lessThan)){
        if(!killswitch.Value())kill = true;
        LCD.WriteAt(pin.Value(), 0, 20);
    }
}

void Robot::waitForPin(DigitalInputPin pin, bool value) {
    while(!kill && pin.Value() != value)
        if(!killswitch.Value())kill = true;
}

void Robot::waitFor(float time) {
    float startTime = TimeNow();
    while(!kill && TimeNow() - startTime < time)
        if(!killswitch.Value())kill = true;
}
