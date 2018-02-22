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
    r.moveAtAngle(0.558505, motor_power);
    r.waitFor(3);
    r.stopAll();
    r.turn(1.5707963, motor_power);
    r.stopAll();
    r.moveAtAngle(PI, motor_power);
    r.waitFor(2);
    r.stopAll();
    r.moveAtAngle(0, motor_power);
    r.waitFor(2);
    r.stopAll();
}
