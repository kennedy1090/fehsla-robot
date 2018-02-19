#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "tests.h"
int main(void)
{

    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    AnalogInputPin cds(FEHIO::P0_0);
    Tests::testPin(cds);
}
