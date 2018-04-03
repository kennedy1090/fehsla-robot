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

#define OFFSET_TIME 0.2
#define OFFSET_ANGLE 3.14159265/2

//within 0.4 radians
#define ANGLE_TOLERANCE 0.1
#define ANGLE2 1
//within 1 inch
#define POSITION_TOLERANCE 0.5
#define POS2 5

#define PULSE_TIME 0.25

#define LOWEST 0.3

#define KILLSWITCH_PIN FEHIO::P1_0
#define CDS_PIN FEHIO::P0_0

#define WRENCH_MIN 500
#define WRENCH_MAX 2377

#define WHEEL_MIN 512
#define WHEEL_MAX 2500

#define DEBUG true

enum Motors {RIGHT = 0, TOP = 1, LEFT = 2, BOTTOM = 3};

struct Point {
    float x, y;
};
class Robot
{
public:
    Robot(bool rps);
    //Angles are in radians
    void moveAtAngle(float angle, float percent);
    void turn(float angle, float percent, bool slow);
    void moveToLocation(Point pos, float percent, bool slow);
    void updateLocation();
    void setMotor(Motors m, float percent);

    void goAndStop(float angle, float percent, float time, bool stop = 0);

    void stop(Motors m);
    void stopAll();

    void waitForPin(AnalogInputPin pin, float threshold, bool lessThan);
    void waitForPin(DigitalInputPin pin, bool value);
    //Both of these slow down by default
    void waitTurnToAngle(float angle, float percent, float tolerance = ANGLE_TOLERANCE);
    void waitMoveToLocation(Point pos, float percent, float tolerance = POSITION_TOLERANCE);
    void waitFor(float time);

    void pulse(Point location, float percent, float tolerance);
    void pulseAngle(float angle, float percent, float tolerance);

    DigitalInputPin killswitch;
    AnalogInputPin cds;

    FEHServo wrench;
    FEHServo wheel;
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
