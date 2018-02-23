#include "robot.h"

inline float wrapAngle( float angle )
{
    double twoPi = 2.0 * PI;
    return angle - twoPi * floor( angle / twoPi );
}

Robot::Robot() :
    right(FEHMotor::Motor0, 7.2), top(FEHMotor::Motor1, 7.2),
    left(FEHMotor::Motor2, 7.2), bottom(FEHMotor::Motor3, 7.2),
    killswitch(KILLSWITCH_PIN), cds(CDS_PIN), kill(false)
{
    currentLocation = {0, 0};
    currentAngle = 0;
}

void Robot::moveToPosition(Point pos, float percent) {
    if(kill)return;
    float angle = atan2(pos.y - currentLocation.y, pos.x - currentLocation.x);
    angle -= currentAngle;
    angle = wrapAngle(angle);
    moveAtAngle(angle, percent);
}

void Robot::moveAtAngle(float angle, float percent) {
    if(kill)return;
    float vRight = percent * cos(angle);
    float vUp = percent * sin(angle);
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
void Robot::turn(float angle, float percent) {
    if(kill)return;
    bool pos = (angle > currentAngle && angle - currentAngle < 3.1415) || (currentAngle > angle && currentAngle - angle  > 3.1415);
    int sign = pos * 2 - 1;
    setMotor(RIGHT, sign * percent);
    setMotor(LEFT, -sign * percent);
    setMotor(TOP, -sign * percent);
    setMotor(BOTTOM, sign * percent);
}

void Robot::updateLocation() {
    if(kill)return;
    currentLocation.x = RPS.X();
    currentLocation.y = RPS.Y();
    currentAngle = RPS.Heading() * 3.1415926535 / 180;
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
        left.SetPercent(1.4*percent);
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
void Robot::waitForLocation(Point location) {
    while(!kill
            && abs(currentLocation.x - location.x) > POSITION_TOLERANCE
            && abs(currentLocation.y - location.y) > POSITION_TOLERANCE) {
        updateLocation();
        if(!killswitch.Value())kill = true;
    }

}

/*
 * Waits until the robot is within ANGLE_TOLERANCE of angle.
 */
void Robot::waitForAngle(float angle) {
    while(!kill && abs(currentAngle - angle) > ANGLE_TOLERANCE) {
        updateLocation();
        if(!killswitch.Value())kill = true;
    }
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
