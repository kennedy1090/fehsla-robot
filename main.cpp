#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "tests.h"

int main(void){
    Point jack = {5, 7.2};
    Point wrench = {9.5, 16.8};

    Point by_start = {15, 19};

    Point white_button = {25.8, 21};
    Point red_button = {white_button.x - 3.5, white_button.y};
    Point blue_button = {white_button.x +  3.5, white_button.y};

    Point bottom_ramp = {29.5, 23.5};
    Point top_ramp = {28.8, 43.1};
    Point by_garage = {16.5, 55.5};
    Point above_wheel = {22, 65};
    Point below_wheel = {24, 63};
    Point by_wheel = {23, 63.2};
    Point at_wheel = {24, 64.4};

    float colorBoundary = 0.55;

    Robot r(true);

    int move_power = 50;
    int turn_power = 40;

    r.wrench.SetDegree(0);
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(0);
    } else {
        r.wheel.SetDegree(180);
    }

    r.waitForPin(r.cds, 1.2, true);

    //Jack
    r.waitMoveToLocation(jack, move_power, false, 1);
    r.stopAll();
    r.waitFor(0.3);
    r.waitMoveToAngle(PI, turn_power);
    r.moveAtAngle(PI, move_power);
    r.waitFor(1);
    r.stopAll();
    r.waitFor(0.2);
    r.moveAtAngle(0, move_power);
    r.waitFor(0.3);
    r.stopAll();
    r.waitFor(0.3);

    //Wrench
    r.waitMoveToLocation(wrench,  move_power);
    r.waitMoveToAngle(PI/2, turn_power, true, 0.08);
    r.wrench.SetDegree(102);
    r.waitFor(1);
    r.moveAtAngle(PI/2, move_power);
    r.waitFor(0.5);
    r.stopAll();
    r.wrench.SetDegree(0);
    r.waitMoveToLocation(by_start, move_power);

    //Button panel
    r.waitMoveToLocation(white_button, move_power);
    float color = r.cds.Value();
    LCD.WriteAt(color, 0, 0);
    r.waitFor(5);
    r.waitMoveToAngle(PI/2, turn_power);
    //drive into RPS button
    r.moveAtAngle(PI, 30);
    r.waitFor(1);
    r.stopAll();
    while(RPS.IsDeadzoneActive() != 2) {
        r.waitFor(1);
    }
    r.moveAtAngle(0, 30);
    r.waitFor(0.5);
    r.stopAll();
    Point button;
    if(color < colorBoundary) {
        button = red_button;
    } else {
        button = blue_button;
    }
    r.waitMoveToLocation(button, move_power);
    r.moveAtAngle(PI, 30);
    r.waitFor(1);
    r.stopAll();
    r.waitFor(1);

    //Ramp
    r.waitMoveToLocation(bottom_ramp, move_power);
    r.waitMoveToAngle(PI/4, 35);

    r.moveAtAngle(PI/4, 70);
    r.waitFor(3);

    r.waitMoveToLocation(top_ramp, move_power);
    r.turn(1, 30, false);
    r.waitFor(0.5);
    r.stopAll();
    r.waitFor(0.5);

    //Garage
    r.waitMoveToLocation(by_garage, move_power, true, 1);
    r.waitMoveToAngle(PI/4, move_power);
    r.moveAtAngle(PI/2, move_power);
    r.waitFor(2);
    r.stopAll();
    r.wrench.SetDegree(102);
    r.waitFor(2);
    r.moveAtAngle(3*PI/2, move_power);
    r.waitFor(2);
    r.wrench.SetDegree(0);
    r.waitMoveToLocation(by_garage, move_power, true, 1);

    //Wheel
    r.waitMoveToAngle(3*PI/4, 40);
    if(RPS.FuelType() == 1){
        r.waitMoveToLocation(above_wheel, move_power);
    } else {
        r.waitMoveToLocation(below_wheel, move_power);
    }
    r.waitMoveToAngle(3*PI/4, 40, true, 0.08);

    r.waitMoveToLocation(by_wheel, move_power, true, 0.3);
    r.waitMoveToAngle(3*PI/4, 40, true, 0.08);
    r.pulseAngle(3*PI/4-0.1, 20, 0.1);
    r.moveAtAngle(-PI/2, move_power);
    r.waitFor(0.43);
    r.stopAll();

    r.wheel.SetDegree(90);
    r.waitFor(1);
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(180);
    } else {
        r.wheel.SetDegree(0);
    }
    r.waitFor(2);

    //End
    r.waitMoveToLocation(by_garage, move_power, true, 2);
    r.waitMoveToLocation(top_ramp, move_power);
    r.waitMoveToAngle(PI/4, 40, false);
    r.waitMoveToLocation(bottom_ramp, move_power);
    r.waitMoveToLocation(by_start, move_power);
    r.waitMoveToAngle(0, move_power);
    r.moveAtAngle(PI/2, move_power);

    LCD.WriteAt("We did it (maybe)!", 0, 0);
}
