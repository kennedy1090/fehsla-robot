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
    Point jack_side = {12, 12};
    Point wrench = {9.1, 16.2};

    Point by_start = {17.5, 19};
    Point before_end = {17.5, 21};
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
    Point grass_ramp = {5, 24.4};

    float colorBoundary = 1.5;

    Robot r(true);

    int move_power = 50;
    int turn_power = 38;
    int wrench_power = 25;
    int big_speed = 70;

    /*while(true)
    {
    LCD.WriteAt("Motor power: ", 50, 50);
        LCD.WriteAt(move_power, 218, 50);
        LCD.WriteAt("X-Value: ", 50, 100);
        LCD.WriteAt(RPS.X(), 218, 100);
        LCD.WriteAt("Y-Value: ", 50, 150);
        LCD.WriteAt(RPS.Y(), 218, 150);
        LCD.WriteAt("Heading: ", 50, 200);
        LCD.WriteAt(RPS.Heading(), 218, 200);
    }*/

    r.wrench.SetDegree(0);
    r.wheel.SetDegree(90);

    r.waitForPin(r.cds, 1.2, true);

    //Button panel

    //Move to the led blind
    r.moveAtAngle(2.29, big_speed);
    r.waitFor(0.25);

    //Adjust to the exact position
    r.waitMoveToLocation(white_button, move_power);
    r.waitTurnToAngle(PI - 0.05, turn_power, 0.1);
    float color = 0;
    LCD.WriteAt(color, 0, 0);
    r.waitFor(0.1);



    //drive into RPS button
    r.moveAtAngle(PI/2, move_power);
    r.waitFor(0.26);
    r.stopAll();
    while(RPS.IsDeadzoneActive() != 2) {
        r.waitFor(1);
    }

    //Hit the correct color button
    Point button;
    if(color < colorBoundary) {
        button = red_button;

        /*Turn to the red button
        r.waitTurnToAngle(1.977458+PI/2, turn_power, 0.1);
        r.moveAtAngle(PI/2, 30);
        r.waitFor(0.1);
        r.stopAll();

        r.moveAtAngle(PI/4, big_speed);
        r.waitFor(0.2);
        r.stopAll();
        r.waitFor(0.5);*/


    } else {
        button = blue_button;

        /*Move to the blue button
        r.waitTurnToAngle(1.097812+PI/2, turn_power, 0.1);
        r.moveAtAngle(PI/2, 30);
        r.waitFor(0.1);
        r.stopAll();

        r.moveAtAngle(3*PI/4, big_speed);
        r.waitFor(0.2);
        r.stopAll();
        r.waitFor(0.5);*/
    }


    //Jack

    //Move to Jack Blind
    r.moveAtAngle(3*PI/2, big_speed);
    r.waitFor(0.15);
    r.waitTurnToAngle(PI, turn_power, 0.1);
    r.moveAtAngle(0 , big_speed);
    r.waitFor(1.4);
    r.stopAll();
    r.wrench.SetDegree(115);

    //Make correct adjustments
    r.waitMoveToLocation(jack_side, move_power, 0.3);
    r.stopAll();

    //Turn to correct angle for Jack
    r.waitTurnToAngle(PI, turn_power, 0.1);


    //Back up while raising the servo angle
    r.wrench.SetDegree(80);
    r.moveAtAngle(3*PI/2, big_speed);
    r.waitFor(0.1);


    /*r.waitFor(0.3);
    r.waitTurnToAngle(PI, turn_power);
    r.moveAtAngle(PI, move_power);
    r.waitFor(1);
    r.stopAll();
    r.waitFor(0.2);
    r.moveAtAngle(0, move_power);
    r.waitFor(0.3);
    r.stopAll();
    r.waitFor(0.3);*/

    //Wrench
    r.waitMoveToLocation(wrench,  move_power, 0.2);
    r.waitTurnToAngle(PI/2, turn_power, 0.08);
    r.pulseAngle(PI/2, turn_power*LOWEST, 0.05);
    r.wrench.SetDegree(107);
    r.waitFor(0.5);
    r.moveAtAngle(PI/2, wrench_power);
    r.waitFor(0.74);
    r.stopAll();
    r.wrench.SetDegree(0);
    r.waitFor(0.3);

    //Grass Ramp
    r.waitMoveToLocation(grass_ramp, move_power);
    r.waitTurnToAngle(PI/4, 35);
    r.moveAtAngle(PI/4 - 0.12, 70);
    r.waitFor(3);

    //Garage
    r.waitMoveToLocation(by_garage, move_power);
    r.waitTurnToAngle(PI/4-0.08, turn_power, 0.05);
    r.moveAtAngle(PI/2, big_speed);
    r.waitFor(1);
    r.stopAll();
    r.wrench.SetDegree(105);
    r.waitFor(2);
    r.moveAtAngle(3*PI/2, move_power);
    r.waitFor(1);
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
    //r.moveAtAngle(PI/2, big_speed);
    //r.waitFor(0.4);
    r.waitMoveToLocation(by_garage, move_power, 2);

    r.moveAtAngle(3*PI/2, big_speed);
    r.waitFor(0.6);
    r.waitMoveToLocation(top_ramp, move_power, 2);

    r.moveAtAngle(3*PI/4, big_speed);
    r.waitFor(0.3);
    r.waitMoveToLocation(bottom_ramp, move_power, 2);


    r.waitMoveToLocation(before_end, move_power);
    r.waitTurnToAngle(PI/2, turn_power, 0.1);
    r.waitMoveToLocation(end, big_speed);

    LCD.WriteAt("We did it (maybe)!", 0, 0);


    /*Ramp
    r.waitMoveToLocation(bottom_ramp, move_power);


    r.waitMoveToLocation(top_ramp, move_power);
    r.turn(1, 30, false);
    r.waitFor(0.5);
    r.stopAll();
    r.waitFor(0.5);*/


};
