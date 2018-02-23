#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "tests.h"
int main(void)
{
    int motor_power = 50;
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    LCD.Write("Motor power: ");
    LCD.WriteLine(motor_power);
    //test
    Robot r;

    r.waitForPin(r.cds, 1.2, true);
    r.moveAtAngle(0.85, motor_power);
    r.waitFor(3.1);
    r.stopAll();
    r.waitFor(0.5);
    r.moveAtAngle(PI, motor_power);
    r.waitFor(0.8);
    r.stopAll();
    r.waitFor(0.5);
    r.moveAtAngle(0, motor_power);
    r.waitFor(0.8);
    r.stopAll();
    r.waitFor(0.5);
    r.moveAtAngle(-2.5, motor_power);
    r.waitFor(2.2);
    r.moveAtAngle(PI, motor_power);
    r.waitFor(2.5);
    r.stopAll();
    r.waitFor(0.5);
    r.moveAtAngle(PI/2, motor_power);
    r.waitFor(0.7);
    r.moveAtAngle(-PI/2, motor_power);
    r.waitFor(0.7);
    r.turn(1, motor_power);
    r.waitFor(0.36);
    r.stopAll();
    r.waitFor(0.5);
    r.moveAtAngle(-2.5, 70);
    r.waitFor(4);
    r.stopAll();
}
