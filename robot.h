#ifndef ROBOT_H
#define ROBOT_H

#include <FEHMotor.h>
#include <stdlib.h>
#include <FEHIO.h>
#include <math.h>

enum Motors {RIGHT = 0, TOP = 1, LEFT = 2, BOTTOM = 3};

struct Point {
    float x, y;
};

class Robot
{
public:
    Robot();
    const float countsPerInch;
    const float radius;
    //Angles are in radians
    void moveAtAngle(float angle, int percent);
    void turn(float angle);
    void moveToPosition(Point pos, float percent);
    void stopAll();
    void updateLocation();
    //Assumes counts have been reset before moving
    bool atLocationDR();
    void setMotor(Motors m, float percent);
    void stop(Motors m);
private:
    FEHMotor right;
    FEHMotor left;
    FEHMotor top;
    FEHMotor bottom;
    Point currentLocation;
    float currentAngle;
    //-1 if motors are running in a negative direction
    //1 if motors are running in a positive direction
    char dirs[4];
    DigitalEncoder rCounts, lCounts;
    DigitalEncoder tCounts, bCounts;
};

#endif // ROBOT_H
