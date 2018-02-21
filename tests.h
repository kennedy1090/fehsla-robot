#ifndef TESTS_H
#define TESTS_H

#include <FEHIO.h>
#include <robot.h>
#include <FEHLCD.h>
#include <FEHRPS.h>

class Tests
{
public:
    Tests(Robot r);
    static void testPin(AnalogInputPin test);
    static void testRPS();
private:
    Robot robot;
};

#endif // TESTS_H
