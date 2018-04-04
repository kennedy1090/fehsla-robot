#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHBattery.h>

#include "tests.h"

Point getCoordinates(char* name, Robot r, bool heading, int number) {
    LCD.Clear();
    LCD.WriteAt(name, 100, 100);
    float x, y;
    Point p;
    while(!LCD.Touch(&x, &y)){

        if (heading == 1){
            switch (number)
            {
            case 1:
                p.heading_1 = (RPS.Heading() * (PI/180.0)) + PI/2;
                break;

            case 2:
                p.heading_2 = (RPS.Heading() * (PI/180.0)) + PI/2;
                break;

            case 3:
                p.heading_3 = (RPS.Heading() * (PI/180.0)) + PI/2;
                break;
            }
        }
        r.updateLocation();
    }

    p.x = RPS.X();
    p.y = RPS.Y();
    return p;
}

int main(void){
    //Point jack_side = {12, 12.3};

    //Point wrench = {9.13, 16.4};

    //Point by_start = {17.5, 19};
    Point before_end = {17.5, 21.5};
    Point end = {17.5, 40};

    Point white_button = {25.8, 20};

    Point bottom_ramp = {28.5, 21.5};
    Point top_ramp = {29.5, 41.7};

    //Point by_garage = {16.5, 55};
    Point by_garage_2 = {22, 47.5};

    //Point by_wheel = {25.9 , 60.4};

    Point grass_ramp = {4.5, 23};

    float colorBoundary = 1;
    float x,y, heading_1, heading_2, heading_3;

    Robot r(true);

    Sleep(0.2);
    Point jack_side = getCoordinates("Side of Jack", r, 0, 0);
    LCD.Clear();
    LCD.WriteAt("Saved!", 100, 100);
    Sleep(0.2);

    Point wrench = getCoordinates("Wrench", r, 1, 1);
    LCD.Clear();
    LCD.WriteAt("Saved!", 100, 100);
    Sleep(0.2);

    Point by_garage = getCoordinates("By garage", r, 1, 2);
    LCD.Clear();
    LCD.WriteAt("Saved!", 100, 100);
    Sleep(0.2);

    Point by_wheel = getCoordinates("By wheel", r, 1, 3);
    LCD.Clear();
    LCD.WriteAt("Saved!", 100, 100);
    Sleep(0.2);

    LCD.Clear();
    Sleep(0.2);
    LCD.WriteAt("Touch the Screen to Start!", 0, 100);
    while(!LCD.Touch(&x, &y));
    LCD.Clear();
    LCD.WriteAt("Ready", 100,100);
    Sleep(0.25);
    LCD.Clear();

    int move_power = 56;
    int turn_power = 40;
    int wrench_power = 30;
    int big_speed = 70;
    int max_speed = 100;

    //Initialize servos
    r.wrench.SetDegree(0);
    r.wheel.SetDegree(90);

    //Start light
    r.waitForPin(r.cds, 1.2, true);

    //Button panel

    //Move to the led blind
    r.goAndStop(2.29, big_speed + 5, 0.3, 1);

    //Adjust to the exact position
    r.waitMoveToLocation(white_button, move_power - 5);
    r.waitTurnToAngle(PI - 0.05, turn_power, 0.1);
    r.waitFor(0.1);

    //drive into RPS button
    r.goAndStop(PI/2, move_power + 8, 0.25, 1);

    //Makes sure RPS is on
    while(RPS.IsDeadzoneActive() != 2) {
        r.waitFor(1);
    }

    //Back up
    r.goAndStop(3*PI/2, big_speed, 0.15);

    //Hit the correct color button
    if(r.cds.Value() < colorBoundary) {
        r.goAndStop(PI/4 - 0.33, big_speed - 5, 0.575);
        r.goAndStop(3*PI/2, big_speed, 0.25);

        //Move to wrench
        r.waitTurnToAngle(PI, turn_power, 0.1);
        r.goAndStop(0.2, big_speed + 10, 1.25);
    }

    else {
        r.goAndStop(3*PI/4 + 0.33, big_speed - 5, 0.587);
        r.goAndStop(-PI/4 + 0.33, big_speed, 0.3);

        //Move a little extra
        r.goAndStop(0, big_speed + 10, 0.5);

        //Move to wrench
        r.waitTurnToAngle(PI, turn_power, 0.1);
        r.goAndStop(0.2, big_speed + 10, 0.8);
    }

    //Jack
    r.wrench.SetDegree(120);

    //Make correct adjustments
    r.goAndStop(PI/2, big_speed, 0.35);

    //Turn to correct angle for Jack
    r.waitTurnToAngle(PI, turn_power, 0.07);
    r.pulseAngle(PI, turn_power, 0.07);

    r.waitMoveToLocation(jack_side, move_power, 0.58);
    r.stopAll();

    //Back up while raising the servo angle
    r.wrench.SetDegree(60);
    r.goAndStop(3*PI/2, big_speed, 0.1);

    //Wrench
    r.waitMoveToLocation(wrench, move_power, 0.4);
    //r.waitTurnToAngle(PI/2, turn_power, 0.05);
    r.waitTurnToAngle(heading_1 + PI/2, turn_power - 5, 0.09);
    //r.pulseAngle(PI/2, turn_power*LOWEST, 0.05);
    r.pulseAngle(heading_1 + PI/2 - 0.02, turn_power - 5, 0.02);
    r.wrench.SetDegree(103);
    r.waitFor(0.1);
    r.goAndStop(PI/2, wrench_power, 0.57, 1);
    r.wrench.SetDegree(0);
    r.waitFor(0.1);

    //Grass Ramp
    r.waitMoveToLocation(grass_ramp, move_power, 0.5);
    r.waitTurnToAngle(PI/4 - 0.05, 35, 0.1);
    r.moveAtAngle(PI/4 - 0.05, big_speed + 15);
    r.waitFor(3.05);

    //Garage
    r.waitMoveToLocation(by_garage, max_speed, 0.5);
    r.pulse(by_garage, move_power, 0.25);
    //r.waitTurnToAngle(PI/4 - 0.14, turn_power - 5, 0.08);
    r.waitTurnToAngle(heading_2 + PI/4 - 0.04, turn_power, 0.05);
    r.goAndStop(PI/2, big_speed, 1, 1);
    r.wrench.SetDegree(110);
    r.waitFor(0.5);

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
    //r.waitTurnToAngle(3*PI/4 - 0.035, turn_power, 0.05);
    r.waitTurnToAngle(heading_3 + 3*PI/4 - 0.035, turn_power, 0.05);

    //Move to the wheel
    r.waitMoveToLocation(by_wheel, move_power, 0.2);
    r.goAndStop(-PI/2, move_power, 0.5, 1);

    //Turn the fuel pump
    r.wheel.SetDegree(90);
    r.waitFor(0.5);
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(180);
    } else {
        r.wheel.SetDegree(0);
    }
    r.waitFor(0.25);

    //End
    r.goAndStop(3*PI/4 - 0.05, big_speed + 10, 0.5);
    r.waitFor(0.3);
    r.waitMoveToLocation(by_garage_2, move_power, 2);

    //Move to top of ramp
    r.goAndStop(PI, big_speed + 20, 0.45);
    r.waitFor(0.3);
    r.waitMoveToLocation(top_ramp, move_power, 2);

    //Move to bottom of ramp
    r.goAndStop(3*PI/4, max_speed, 0.57);
    r.waitFor(0.3);
    r.waitMoveToLocation(bottom_ramp, move_power, 1.5);

    //Move to before the end
    r.goAndStop(PI/4 - 0.2, big_speed + 25, 0.62);
    r.waitFor(0.3);
    r.waitMoveToLocation(before_end, move_power);

    //Turn and move to end
    //r.waitTurnToAngle(PI, turn_power, 0.3);
    r.waitMoveToLocation(end, big_speed);

    //LCD.WriteAt("We did it (maybe)!", 0, 0);
}
