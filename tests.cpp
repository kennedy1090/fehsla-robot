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
}
