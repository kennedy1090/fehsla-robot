#ifndef ROBOT_H
#define ROBOT_H

#include <FEHMotor.h>
#include <FEHRPS.h>
#include <stdlib.h>
#include <FEHIO.h>
#include <math.h>
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHServo.h>
#include <FEHSD.h>

#define PI 3.14159265

#define OFFSET_TIME 0.3
#define OFFSET_ANGLE 3*3.14159265/2

//within 0.2 radians
#define ANGLE_TOLERANCE 0.1
#define ANGLE2 1
//within 1 inch
#define POSITION_TOLERANCE 0.5
#define POS2 5

#define LOWEST 0.3

#define KILLSWITCH_PIN FEHIO::P1_0
#define CDS_PIN FEHIO::P3_7

#define SERVO_MIN 500
#define SERVO_MAX 2377

#define DEBUG true

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
    void turn(float angle, float percent, bool slow);
    void moveToPosition(Point pos, float percent, bool slow);
    void updateLocation();
    void setMotor(Motors m, float percent);

    void stop(Motors m);
    void stopAll();

    void waitForPin(AnalogInputPin pin, float threshold, bool lessThan);
    void waitForPin(DigitalInputPin pin, bool value);
    void waitMoveToAngle(float angle, float power, bool slow);
    void waitMoveToLocation(Point pos, float percent, bool slow);
    void waitFor(float time);

    DigitalInputPin killswitch;
    AnalogInputPin cds;
    FEHServo wrench;
private:


    bool kill;

    FEHMotor right;
    FEHMotor left;
    FEHMotor top;
    FEHMotor bottom;

    Point velocity;
    float angularV;

    Point currentLocation;
    float currentAngle;

    float lastTime;
};

#endif // ROBOT_H
