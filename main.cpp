#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHBattery.h>

#include "tests.h"
Point getCoordinates(char* name, Robot r) {
    LCD.Clear();
    LCD.WriteAt(name, 100, 100);
    float x, y;
    Point p;
    while(!LCD.Touch(&x, &y)){
        r.updateLocation();
    }
    p.x = RPS.X();
    p.y = RPS.Y();
    return p;
}

int main(void){
    //Point jack_side = {12, 12.3};

    Point wrench = {9.13, 16.4};

    //Point by_start = {17.5, 19};
    Point before_end = {17.5, 21.5};
    Point end = {17.5, 40};

    Point white_button = {25.8, 20};

    Point bottom_ramp = {28.5, 21.5};
    Point top_ramp = {29.5, 41.7};

    Point by_garage = {16.5, 55};
    Point by_garage_2 = {17, 52};

    //Point by_wheel = {25.9 , 60.4};

    Point grass_ramp = {4.5, 23};

    float colorBoundary = 1;

    Robot r(true);

    Point jack_side = getCoordinates("Side of Jack", r);
    Point by_wheel = getCoordinates("By wheel", r);

    int move_power = 55;
    int turn_power = 38;
    int wrench_power = 30;
    int big_speed = 70;

    //Initialize servos
    r.wrench.SetDegree(0);
    r.wheel.SetDegree(90);

    //Start light
    r.waitForPin(r.cds, 1.2, true);

    //Button panel

    //Move to the led blind
    r.goAndStop(2.29, big_speed + 10, 0.5, 1);

    //Adjust to the exact position
    r.waitMoveToLocation(white_button, move_power);
    r.waitTurnToAngle(PI - 0.05, turn_power, 0.1);
    r.waitFor(0.1);

    //drive into RPS button
    r.goAndStop(PI/2, move_power, 0.21, 1);

    //Makes sure RPS is on
    while(RPS.IsDeadzoneActive() != 2) {
        r.waitFor(1);
    }

    //Back up
    r.goAndStop(3*PI/2, big_speed, 0.15);

    //Hit the correct color button
    if(r.cds.Value() < colorBoundary) {
        r.goAndStop(PI/4 - 0.33, big_speed - 5, 0.57);
        r.goAndStop(PI/4 - 0.33 + PI, big_speed, 0.3);

        //Move a little extra
        r.goAndStop(0, big_speed + 20, 0.5);

        //Move to wrench
        r.waitTurnToAngle(PI, turn_power, 0.1);
        r.goAndStop(0.2, big_speed + 10, 0.8);
    }

    else {
        r.goAndStop(3*PI/4 + 0.33, big_speed - 5, 0.57);
        r.goAndStop(3*PI/4 + 0.33 + PI, big_speed, 0.3);

        //Move to wrench
        r.waitTurnToAngle(PI, turn_power, 0.1);
        r.goAndStop(0.2, big_speed + 10, 1.3);
    }

    //Jack
    r.wrench.SetDegree(120);

    //Make correct adjustments
    r.waitMoveToLocation(jack_side, move_power, 0.57);
    r.stopAll();

    //Turn to correct angle for Jack
    r.waitTurnToAngle(PI, turn_power, 0.1);

    //Back up while raising the servo angle
    r.wrench.SetDegree(80);
    r.moveAtAngle(3*PI/2, big_speed);
    r.waitFor(0.1);

    //Wrench
    r.waitMoveToLocation(wrench, move_power, 0.23);
    r.waitTurnToAngle(PI/2, turn_power, 0.08);
    r.pulseAngle(PI/2, turn_power*LOWEST, 0.05);
    r.wrench.SetDegree(107);
    r.waitFor(0.1);
    r.goAndStop(PI/2, wrench_power, 0.6, 1);
    r.wrench.SetDegree(0);
    r.waitFor(0.1);

    //Grass Ramp
    r.waitMoveToLocation(grass_ramp, move_power, 0.34);
    r.waitTurnToAngle(PI/4, 35);
    r.moveAtAngle(PI/4 - 0.2, big_speed + 25);
    r.waitFor(2.5);

    //Garage
    r.waitMoveToLocation(by_garage, move_power + 25, 0.25);
    r.waitTurnToAngle(PI/4 - 0.14, turn_power - 5, 0.05);
    r.goAndStop(PI/2, big_speed, 1, 1);
    r.wrench.SetDegree(110);
    r.waitFor(1);

    //Back out Diagonally
    r.goAndStop(-PI/4, big_speed + 10, 1, 1);
    r.wrench.SetDegree(0);

    //Checks the fuel type
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(0);
    } else {
        r.wheel.SetDegree(180);
    }

    //Wheel

    //Turns robot to correct angle
    r.waitTurnToAngle(3*PI/4 - 0.035, turn_power);

    //Move to the wheel
    r.waitMoveToLocation(by_wheel, move_power);
    r.goAndStop(-PI/2, move_power, 0.5, 1);

    //Turn the fuel pump
    r.wheel.SetDegree(90);
    r.waitFor(0.5);
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(180);
    } else {
        r.wheel.SetDegree(0);
    }
    r.waitFor(0.5);

    //End
    r.goAndStop(PI/2, big_speed, 0.4);
    r.waitMoveToLocation(by_garage_2, move_power, 2);

    //Move to top of ramp
    r.goAndStop(PI, big_speed + 10, 0.6);
    r.waitMoveToLocation(top_ramp, move_power, 2);

    //Move to bottom of ramp
    r.goAndStop(3*PI/4, big_speed + 30, 0.6);
    r.waitMoveToLocation(bottom_ramp, move_power, 1.8);

    //Move to before the end
    r.goAndStop(PI/4 - 0.2, big_speed + 25, 0.67);
    r.waitMoveToLocation(before_end, move_power);

    //Turn and move to end
    //r.waitTurnToAngle(PI, turn_power, 0.3);
    r.waitMoveToLocation(end, big_speed);

    LCD.WriteAt("We did it (maybe)!", 0, 0);
}
