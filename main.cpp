#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "tests.h"

int main(void){
    Point jack = {};
    Point wrench = {};

    Point button_panel = {25.8, 21.5};
    Point bottom_ramp = {28.8, 24.5};
    Point top_ramp = {28.8, 43.1};
    Point by_garage = {16.5, 55.5};
    Point at_wheel = {24.2, 64.4};

    Robot r(true);

    int move_power = 50;
    int turn_power = 20;

    r.wrench.SetDegree(0);
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(0);
    } else {
        r.wheel.SetDegree(180);
    }

    r.waitForPin(r.cds, 1.2, true);
    /*
    r.waitMoveToLocation(jack, move_power, false, 1);
    r.moveAtAngle(0, move_power);
    r.waitFor(1);
    r.stopAll();
    r.waitFor(0.2);


    r.waitMoveToLocation(wrench,  move_power, true);
    r.waitMoveToAngle(PI/2, turn_power, false);

    */

    r.waitMoveToLocation(button_panel, move_power, true);
    r.waitMoveToAngle(PI, turn_power, true);
    r.moveAtAngle(PI/2, 30);
    r.waitFor(1);
    r.stopAll();
    r.waitFor(6);

    r.waitMoveToLocation(bottom_ramp, move_power, true);
    r.waitMoveToAngle(PI/4, 20, false);

    r.moveAtAngle(PI/4, 60);
    r.waitFor(3);

    r.waitMoveToLocation(top_ramp, move_power, true);

    r.waitMoveToLocation(at_wheel, move_power, true);
    r.waitMoveToAngle(3*PI/4, 20, false);

    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(180);
    } else {
        r.wheel.SetDegree(0);
    }
    r.waitMoveToLocation(top_ramp, move_power, false);
    r.waitMoveToAngle(PI/4, 40, false);
    r.waitMoveToLocation(bottom_ramp, move_power, false);

}
