#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "tests.h"

int main(void)
{
    Robot r;

    struct Point xy_pos;

    int motor_power = 50;

    /*LCD.WriteAt("Motor power: ", 50, 50);
    LCD.WriteAt(motor_power, 218, 50);

    LCD.WriteAt("Heading: ", 50, 200);
    LCD.WriteAt(RPS.Heading(), 218, 200);*/

    r.wrench.SetDegree(0);
    Sleep(2.0);
    r.wrench.SetDegree(95);
    //r.waitForPin(r.cds, 1.2, true);

    xy_pos.x = 25.8;
    xy_pos.y = 21.5;
    r.waitMoveToLocation(xy_pos, motor_power);

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
