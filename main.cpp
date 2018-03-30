#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHBattery.h>

#include "tests.h"
Point getCoordinates() {
    float x, y;
    Point p;
    while(!LCD.Touch(&x, &y));
    p.x = RPS.X();
    p.y = RPS.Y();
    return p;
}

int main(void){
    Point jack = {5, 7.2};
    Point wrench = {9.1, 16.2};

    Point by_start = {17.5, 19};
    Point end = {17.5, 40};

    Point white_button = {25.8, 20};
    Point red_button = {white_button.x - 3.5, white_button.y};
    Point blue_button = {white_button.x +  3.5, white_button.y};

    Point bottom_ramp = {29.5, 22.5};
    Point top_ramp = {28.8, 42.1};
    Point by_garage = {16.5, 55};
    Point above_wheel = {20, 62};
    Point below_wheel = {22, 58};
    Point by_wheel = {25.7, 60.7};
    Point at_wheel = {26.6, 61.5};

    float colorBoundary = 1.5;

    Robot r(true);

    int move_power = 50;
    int turn_power = 40;
    int wrench_power = 25;

    r.wrench.SetDegree(0);
    r.wheel.SetDegree(90);

    r.waitForPin(r.cds, 1.2, true);

    LCD.WriteAt(Battery.Voltage(), 200, 200);

    //Jack
    r.waitMoveToLocation(jack, move_power, 1);
    r.stopAll();
    r.waitFor(0.3);
    r.waitTurnToAngle(PI, turn_power);
    r.moveAtAngle(PI, move_power);
    r.waitFor(1);
    r.stopAll();
    r.waitFor(0.2);
    r.moveAtAngle(0, move_power);
    r.waitFor(0.3);
    r.stopAll();
    r.waitFor(0.3);

    //Wrench
    r.waitMoveToLocation(wrench,  move_power, 0.2);
    r.waitTurnToAngle(PI/2, turn_power, 0.08);
    r.pulseAngle(PI/2, turn_power*LOWEST, 0.05);
    r.wrench.SetDegree(104);
    r.waitFor(0.5);
    r.moveAtAngle(PI/2, wrench_power);
    r.waitFor(0.74);
    r.stopAll();
    r.wrench.SetDegree(0);
    r.waitFor(0.3);
    r.waitMoveToLocation(by_start, move_power);

    //Button panel
    r.waitMoveToLocation(white_button, move_power);
    float color = 0;
    LCD.WriteAt(color, 0, 0);
    r.waitFor(1);
    r.waitTurnToAngle(PI/2, turn_power);
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
    r.waitMoveToLocation(button, move_power + 10);
    r.moveAtAngle(PI, 30);
    r.waitFor(1);
    r.stopAll();
    r.waitFor(1);


    //Ramp
    r.waitMoveToLocation(bottom_ramp, move_power);
    r.waitTurnToAngle(PI/4, 35);

    r.moveAtAngle(PI/4 - 0.2, 70);
    r.waitFor(3);

    r.waitMoveToLocation(top_ramp, move_power);
    r.turn(1, 30, false);
    r.waitFor(0.5);
    r.stopAll();
    r.waitFor(0.5);

    //Garage
    r.waitMoveToLocation(by_garage, move_power);
    r.waitTurnToAngle(PI/4-0.1, move_power, 0.05);
    r.moveAtAngle(PI/2, move_power);
    r.waitFor(2);
    r.stopAll();
    r.wrench.SetDegree(104);
    r.waitFor(2);
    r.moveAtAngle(3*PI/2, move_power - 15);
    r.waitFor(2);
    r.wrench.SetDegree(0);
    r.waitMoveToLocation(by_garage, move_power);

    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(0);
    } else {
        r.wheel.SetDegree(180);
    }


    //Wheel
    r.waitTurnToAngle(3*PI/4, 40);
    if(RPS.FuelType() == 1){
        r.waitMoveToLocation(above_wheel, move_power);
    } else {
        r.waitMoveToLocation(below_wheel, move_power);
    }
    r.waitTurnToAngle(3*PI/4, 40, 0.08);

    r.waitMoveToLocation(by_wheel, move_power);
    r.waitTurnToAngle(3*PI/4, 40, 0.08);
    r.pulse(by_wheel, move_power*LOWEST, 0.2);
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
    r.waitMoveToLocation(by_garage, move_power, 2);
    r.waitMoveToLocation(top_ramp, move_power, 2);
    r.waitMoveToLocation(bottom_ramp, move_power, 2);
    r.waitMoveToLocation(by_start, move_power);
    r.waitTurnToAngle(0, move_power, 0.08);
    r.waitMoveToLocation(end, move_power);

    LCD.WriteAt("We did it (maybe)!", 0, 0);
}
