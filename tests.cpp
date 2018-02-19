#include "tests.h"

Tests::Tests(Robot r) {

}

void Tests::testPin(AnalogInputPin test) {
    while(true) {
        LCD.WriteAt(test.Value(), 0, 0);
    }
}
