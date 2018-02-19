#include "robot.h"

Robot::Robot()
{
    //TODO: get actual location and angle as reported by RPS
    currentLocation = {300, 200};
    currentAngle = 0;
}

Robot::moveToPosition(Point pos, float percent) {
    angle = atan2(pos.y - currentLocation.y, pos.x - currentLocation.x);
    angle -= currentAngle;
    angle = wrapAngle(angle);
    moveAtAngle(angle, percent);
}

Robot::moveAtAngle(float angle, float percent) {
    float vRight = percent * cos(angle);
    float vUp = percent * sin(angle);
    setMotor(TOP, vRight);
    setMotor(BOTTOM, vRight);
    setMotor(RIGHT, vUp);
    setMotor(LEFT, vUp);
}
Robot::stopAll() {
    stop(TOP);
    stop(BOTTOM);
    stop(RIGHT);
    stop(LEFT);
}
Robot::turn(float angle, float percent) {
    bool pos = (angle > currentAngle && angle - currentAngle < 3.1415) || (currentAngle > angle && currentAngle - angle  > 3.1415);
    int sign = pos * 2 - 1;
    setMotor(RIGHT, sign * percent);
    setMotor(LEFT, -sign * percent);
    setMotor(TOP, -sign * percent);
    setMotor(BOTTOM, sign * percent);
}

Robot::updateLocation() {
    currentLocation.x += (dirs[TOP] * tCounts.Counts() + dirs[BOTTOM] * bCounts.Counts()) / (2 * countsPerInch);
    currentLocation.y += (dirs[LEFT] * lCounts.Counts() + dirs[RIGHT] * rCounts.Counts()) / (2 * countsPerInch);
    currentAngle += ((dirs[TOP] * tCounts.Counts() - dirs[BOTTOM] * bCounts.Counts())
                     + (dirs[RIGHT] * rCounts.Counts() - dirs[LEFT] * lCounts.Counts()))
                  / (2 * countsPerInch * radius);
    currentAngle = wrapAngle(currentAngle);
    //I'm using the counts as a delta value here by resetting them every time we update location
    tCounts.ResetCounts();
    bCounts.ResetCounts();
    lCounts.ResetCounts();
    rCounts.ResetCounts();
}
Robot::setMotor(Motors m, float percent) {
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
    dirs[m] = signbit(percent) * -2 + 1;
}
Robot::stop(Motors m) {
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
    dirs[m] = 0;
}

//Currently this returns true within 1 inch of location
Robot::atLocationDR(struct Point location) {
    bool b = abs(currentLocation.x - location.x) < 1;
    b &= abs(currentLocation.y - location.y) < 1;
    return b;
}

inline float wrapAngle( float angle )
{
    double twoPi = 2.0 * 3.141592865358979;
    return angle - twoPi * floor( angle / twoPi );
}
