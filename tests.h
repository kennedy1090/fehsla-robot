#ifndef TESTS_H
#define TESTS_H

#include <FEHIO.h>
#include <robot.h>
#include <FEHLCD.h>

class Tests
{
public:
    Tests(Robot r);
    static void testPin(AnalogInputPin test);
};

#endif // TESTS_H
