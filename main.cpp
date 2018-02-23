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
    r.waitForPin(r.cds, 1, true);
    r.moveAtAngle(0.85, motor_power);
    r.waitFor(4);
    r.stopAll();
    r.turn(PI/2-1, motor_power);
    r.stopAll();
    r.moveAtAngle(PI, motor_power);
    r.waitFor(2);
    r.stopAll();
    r.moveAtAngle(0, motor_power);
    r.waitFor(2);
    r.stopAll();
}
