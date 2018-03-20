#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "tests.h"

int main(void)
{
    Point button_panel = {25.8, 21.5};
    Point bottom_ramp = {28.8, 24.5};
    Point top_ramp = {28.8, 43.1};
    Point by_garage = {16.5, 55.5};
    Point at_wheel = {24.2, 64.4};


    Robot r;

    int move_power = 50;
    int turn_power = 20;

    /*LCD.WriteAt("Motor power: ", 50, 50);
    LCD.WriteAt(motor_power, 218, 50);

    LCD.WriteAt("Heading: ", 50, 200);
    LCD.WriteAt(RPS.Heading(), 218, 200);*/

    r.wrench.SetDegree(0);
    //r.waitForPin(r.cds, 1.2, true);

    r.waitMoveToLocation(button_panel, move_power, true);
    r.waitMoveToAngle(0, turn_power, true);
    r.moveAtAngle(3*PI/2, 30);
    r.waitFor(1);
    r.stopAll();
    r.waitFor(6);

    r.waitMoveToLocation(bottom_ramp, move_power, true);
    r.waitMoveToAngle(PI/4, 25, false);


    r.waitMoveToLocation(top_ramp, move_power, true);

    r.waitMoveToLocation(at_wheel, move_power, true);
    r.waitMoveToAngle(3*PI/4, 20, false);

}
