#include "robot.h"

inline float wrapAngle( float angle )
{
    double twoPi = 2.0 * 3.141592865358979;
    return angle - twoPi * floor( angle / twoPi );
}

Robot::Robot() : right(FEHMotor::Motor0, 7.2), top(FEHMotor::Motor1, 7.2), left(FEHMotor::Motor2, 7.2), bottom(FEHMotor::Motor3, 7.2)
{
    currentLocation = {RPS.X(), RPS.Y()};
    currentAngle = RPS.Heading() * 3.14159265 / 180;
}

void Robot::moveToPosition(Point pos, float percent) {
    float angle = atan2(pos.y - currentLocation.y, pos.x - currentLocation.x);
    angle -= currentAngle;
    angle = wrapAngle(angle);
    moveAtAngle(angle, percent);
}

void Robot::moveAtAngle(float angle, float percent) {
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
    bool pos = (angle > currentAngle && angle - currentAngle < 3.1415) || (currentAngle > angle && currentAngle - angle  > 3.1415);
    int sign = pos * 2 - 1;
    setMotor(RIGHT, sign * percent);
    setMotor(LEFT, -sign * percent);
    setMotor(TOP, -sign * percent);
    setMotor(BOTTOM, sign * percent);
}

void Robot::updateLocation() {
    currentLocation.x = RPS.X();
    currentLocation.y = RPS.Y();
    currentAngle = RPS.Heading() * 3.1415926535 / 180;
}
void Robot::setMotor(Motors m, float percent) {
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
        left.SetPercent(percent);
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

//Currently this returns true within 1 inch of location
bool Robot::atLocation(Point location) {
    bool b = abs(currentLocation.x - location.x) < 1;
    b &= abs(currentLocation.y - location.y) < 1;
    return b;
}
bool Robot::atAngle(float angle) {
    return abs(currentAngle - angle) < 0.2;
}

