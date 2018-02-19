#ifndef ROBOT_H
#define ROBOT_H

#include <FEHMotor.h>
#include <FEHRPS.h>
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
    //Angles are in radians
    void moveAtAngle(float angle, float percent);
    void turn(float angle, float percent);
    void moveToPosition(Point pos, float percent);
    void stopAll();
    void updateLocation();
    //Assumes counts have been reset before moving
    bool atAngle(float angle);
    bool atLocation(Point p);
    void setMotor(Motors m, float percent);
    void stop(Motors m);
private:
    FEHMotor right;
    FEHMotor left;
    FEHMotor top;
    FEHMotor bottom;
    Point currentLocation;
    float currentAngle;
};

#endif // ROBOT_H
