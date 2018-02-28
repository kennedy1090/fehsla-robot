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
    r.moveAtAngle(2.4, 50);
    r.waitFor(1.42);
    r.stopAll();
    Sleep(0.5);
    r.moveAtAngle(PI, 40);
    r.waitFor(0.52);
    r.stopAll();
    Sleep(1);

    if (r.cds.Value() <= 0.55)
    {
        LCD.WriteAt(r.cds.Value(), 100, 200);
        LCD.WriteAt("Red", 100, 150);
        Sleep(0.5);
        r.moveAtAngle(0, 40);
        r.waitFor(0.6);
        r.stopAll();
        Sleep(0.5);
        r.moveAtAngle(PI/2, 40);
        r.waitFor(0.3);
        r.stopAll();
        Sleep(0.5);
        r.moveAtAngle(3*PI/2, 40);
        r.waitFor(0.45);
        r.stopAll();
        Sleep(0.5);
        r.moveAtAngle(PI, 40);
        r.waitFor(0.3);
        r.stopAll();
        Sleep(0.5);
    }

    else if (r.cds.Value() > 0.55)
    {
        LCD.WriteAt(r.cds.Value(), 100, 200);
        LCD.WriteAt("Blue", 100, 150);
        Sleep(0.5);
        r.moveAtAngle(PI, 40);
        r.waitFor(0.6);
        r.stopAll();
        Sleep(0.5);
        r.moveAtAngle(PI/2, 40);
        r.waitFor(0.3);
        r.stopAll();
        Sleep(0.5);
        r.moveAtAngle(3*PI/2, 40);
        r.waitFor(0.45);
        r.stopAll();
        Sleep(0.5);
        r.moveAtAngle(0, 50);
        r.waitFor(0.6);
    }

    r.moveAtAngle(0, 50);
    r.waitFor(3);
    r.stopAll();
    Sleep(0.5);

    r.moveAtAngle(PI, 50);
    r.waitFor(2);
    r.stopAll();
    Sleep(0.5);

    r.moveAtAngle(3*PI/2, 50);
    r.waitFor(1);
    r.stopAll();

    //red range ~ 0.3 - 0.53
    //blue range ~ 0.53 - 0.95
}
