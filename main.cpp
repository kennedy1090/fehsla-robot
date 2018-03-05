#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "tests.h"

#define MAX 2377
#define MIN 500

int main(void)
{
    Robot r;
    FEHServo Wrench(FEHServo::Servo0);

    struct Point xy_pos;

    int motor_power = 50;

    /*LCD.WriteAt("Motor power: ", 50, 50);
    LCD.WriteAt(motor_power, 218, 50);

    LCD.WriteAt("Heading: ", 50, 200);
    LCD.WriteAt(RPS.Heading(), 218, 200);*/

    Wrench.SetMin(MIN);
    Wrench.SetMax(MAX);
    Wrench.SetDegree(0);
    Sleep(2.0);
    Wrench.SetDegree(95);
    //r.waitForPin(r.cds, 1.2, true);

    xy_pos.x = 0;
    xy_pos.y = 0;
    r.waitMoveToLocation(xy_pos, motor_power);
    LCD.WriteAt("X-Value: ", 50, 100);
    LCD.WriteAt(RPS.X(), 218, 100);
    LCD.WriteAt("Y-Value: ", 50, 150);
    LCD.WriteAt(RPS.Y(), 218, 150);

    //xy_pos.x = 8.3;
    //xy_pos.y = 16.3;
    //r.waitMoveToLocation(xy_pos, motor_power);

    //r.waitMoveToAngle(3.075252689);


    /*xy_pos.x =
    xy_pos.y =
    r.waitMoveToLocation(xy_pos, motor_power);

    xy_pos.x =
    xy_pos.y =
    r.waitMoveToLocation(xy_pos, motor_power);

    xy_pos.x =
    xy_pos.y =
    r.waitMoveToLocation(xy_pos, motor_power);

    xy_pos.x =
    xy_pos.y =
    r.waitMoveToLocation(xy_pos, motor_power);

    xy_pos.x =
    xy_pos.y =
    r.waitMoveToLocation(xy_pos, motor_power);

    xy_pos.x =
    xy_pos.y =
    r.waitMoveToLocation(xy_pos, motor_power);

    r.moveAtAngle();
    r.waitFor();
    r.stopAll();

    r.moveAtAngle();
    r.waitFor();
    r.stopAll();

    r.moveAtAngle();
    r.waitFor();
    r.stopAll();*/

}
