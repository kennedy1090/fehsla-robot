#include "tests.h"

Tests::Tests(Robot r) : robot(r) {
}

void Tests::testPin(AnalogInputPin test) {
    while(true) {
        LCD.WriteAt(test.Value(), 0, 0);
    }
}

void Tests::testRPS() {
    RPS.InitializeTouchMenu();
    DigitalInputPin kill(KILLSWITCH_PIN);
    while(kill.Value()) {
        LCD.WriteAt("X: ", 0,0);
        LCD.WriteAt( RPS.X(), 60, 0);
        LCD.WriteAt("Y: ", 0, 20);
        LCD.WriteAt(RPS.Y(), 60, 20);
        LCD.WriteAt("Heading: " , 0, 40);
        LCD.WriteAt(RPS.Heading(), 60, 40);
        Sleep(0.1);
    }

    /*while(true)
    {
    LCD.WriteAt("Cds Value: ", 50, 50);
        LCD.WriteAt(r.cds.Value(), 218, 50);
        LCD.WriteAt("X-Value: ", 50, 100);
        LCD.WriteAt(RPS.X(), 218, 100);
        LCD.WriteAt("Y-Value: ", 50, 150);
        LCD.WriteAt(RPS.Y(), 218, 150);
        LCD.WriteAt("Heading: ", 50, 200);
        LCD.WriteAt(RPS.Heading(), 218, 200);
        Sleep(0.1);
    }*/
}
