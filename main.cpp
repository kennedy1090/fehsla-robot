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
    AnalogInputPin cds(FEHIO::P0_0);
    Tests::testPin(cds);
}
