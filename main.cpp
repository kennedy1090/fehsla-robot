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
    Robot r;
    r.moveAtAngle(PI/4, motor_power);
    r.waitFor(3);
    r.stopAll();
}
