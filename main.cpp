#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

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

    if (number == 1)
    {
       p.y = p.y + 0.5;
    }

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
    Point top_ramp = {30, 41.7};

    //Point by_garage = {16.5, 55};
    Point by_garage_2 = {23.5, 47.8};

    //Point by_wheel = {25.9 , 60.4};

    Point grass_ramp = {5, 23};

    float colorBoundary = 1;
    float x,y, heading_1, heading_2, heading_3;


    Robot r(true);

    /*while(true)
    {
    LCD.WriteAt("Cds Value: ", 50, 50);
        LCD.WriteAt(r.cds.Value(), 218, 50);
        LCD.WriteAt("X-Value: ", 50, 100);
        LCD.WriteAt(RPS.X(), 218, 100);
        LCD.WriteAt("Y-Value: ", 50, 150);
        LCD.WriteAt(RPS.Y(), 218, 150);
        LCD.WriteAt("Heading: ", 50, 200);
        LCD.WriteAt(RPS.Heading(), 218, 200);
        Sleep(0.1);
    }*/

    LCD.WriteAt("Touch the Screen!", 0, 100);
    while(!LCD.Touch(&x, &y));
    LCD.Clear();

    Sleep(0.1);
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

    int pulse_angle_speed = 20;
    int pulse_location_speed =20;
    int turn_power = 42;

    int wrench_power = 40;
    int move_power = 60;
    int move_power_2 = 70;
    int max_speed = 100;
    int diagonal_max_speed = 140;

    //Initialize servos
    r.wrench.SetDegree(0);
    r.wheel.SetDegree(90);

    //---------------Start light---------------
    r.waitForPin(r.cds, 1.2, true);

    //---------------Button panel---------------

    //Move to the led blind
    r.goAndStop(2.29, max_speed, 0.39, 1);

    //Adjust to the exact position
    r.waitMoveToLocation(white_button, move_power - 5);
    r.waitTurnToAngle(PI - 0.05, turn_power, 0.1);
    r.waitFor(0.05);

    //drive into RPS button
    r.goAndStop(PI/2, move_power, 0.27, 1);

    //Makes sure RPS is on
    while(RPS.IsDeadzoneActive() != 2) {
        r.waitFor(0.1);
    }

    //Back up
    r.goAndStop(3*PI/2, max_speed, 0.12);

    //Hit the correct color button

    //red
    if(r.cds.Value() < colorBoundary) {
        r.goAndStop(PI/4, move_power_2 - 5, 0.557);
        r.goAndStop(3*PI/2, move_power_2, 0.25);

        //Move to jack
        r.waitTurnToAngle(PI, turn_power - 5, 0.1);
        r.goAndStop(0.2, max_speed, 0.6);
    }

    //blue
    else {
        r.goAndStop(3*PI/4, move_power_2 - 5, 0.557);
        r.goAndStop(-PI/4, max_speed, 0.25);

        r.waitFor(0.1);
        //Move a little extra
        r.goAndStop(0, max_speed, 0.5);
        r.waitFor(0.1);

        //Move to jack
        r.waitTurnToAngle(PI, turn_power - 5, 0.1);
        r.goAndStop(0.15, max_speed, 0.45);
    }

    //---------------Jack---------------
    r.wrench.SetDegree(116);

    //Make correct adjustments
    r.goAndStop(PI/2, max_speed, 0.2);

    //Turn to correct angle for Jack
    r.waitTurnToAngle(PI, turn_power, 0.07);

    r.waitMoveToLocation(jack_side, move_power, 0.5);
    r.stopAll();

    //Back up while raising the servo angle
    r.wrench.SetDegree(60);
    r.goAndStop(3*PI/2, max_speed, 0.07);

    //---------------Wrench---------------
    r.waitMoveToLocation(wrench, move_power, 0.4);
    //r.waitTurnToAngle(PI/2, turn_power, 0.05);
    r.blindTurn(PI/2, 90, 0.38);
    r.stopAll();
    r.waitFor(0.1);

    //r.waitTurnToAngle(heading_1 + PI/2, turn_power - 10, 0.02);
    //r.pulseAngle(PI/2, turn_power*LOWEST, 0.05);
    r.pulseAngle(heading_1 + PI/2, pulse_angle_speed, 0.02);
    r.wrench.SetDegree(103);
    r.waitFor(0.1);
    r.goAndStop(PI/2, wrench_power, 0.57, 1);
    r.wrench.SetDegree(0);
    r.waitFor(0.1);

    //---------------Grass Ramp---------------
    r.waitMoveToLocation(grass_ramp, move_power - 5, 0.6);
    r.waitTurnToAngle(PI/4, turn_power - 15, 0.05);
    r.moveAtAngle(PI/4, diagonal_max_speed - 10);
    r.waitFor(1.45);

    //---------------Garage---------------
    r.waitMoveToLocation(by_garage, move_power + 10, 0.4);
    //r.pulse(by_garage, 15, 0.25);
    //r.waitTurnToAngle(PI/4 - 0.14, turn_power - 5, 0.08);
    r.waitTurnToAngle(heading_2 + PI/4 - 0.04, turn_power, 0.06);
    r.goAndStop(PI/2, max_speed - 10, 0.8, 1);
    r.wrench.SetDegree(110);
    r.waitFor(0.45);

    //Back out Diagonally
    r.goAndStop(-PI/4 - 0.25, max_speed, 0.9, 1);
    r.wrench.SetDegree(0);

    //Checks the fuel type
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(0);
    } else {
        r.wheel.SetDegree(180);
    }

    //---------------Wheel---------------

    //Turns robot to correct angle
    //r.waitTurnToAngle(3*PI/4 - 0.035, turn_power, 0.05);

    //Move to the wheel
    r.waitMoveToLocation(by_wheel, move_power - 10, 0.7);
    r.pulse(by_wheel, pulse_location_speed, 0.1);
    //r.goAndStop(PI, move_power - 20, 0.6, 1);

    //Adjust the angle
    //r.waitTurnToAngle(heading_3 + 3*PI/4 - 0.035, turn_power - 5, 0.04);
    r.blindTurn(PI/2, 90, 0.38);
    r.pulseAngle(heading_3 + 3*PI/4 - 0.035, pulse_angle_speed, 0.04);

    //Run into the fuel pump
    r.goAndStop(-PI/2, move_power + 5, 0.5, 1);

    //Turn the servo for the fuel pump
    r.wheel.SetDegree(90);
    r.waitFor(0.5);
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(180);
    } else {
        r.wheel.SetDegree(0);
    }
    r.waitFor(0.2);

    //---------------End---------------
    r.goAndStop(3*PI/4 - 0.07, max_speed, 0.4);
    r.waitMoveToLocation(by_garage_2, move_power, 2);

    //Move to top of ramp
    r.goAndStop(PI, max_speed, 0.33);
    r.waitMoveToLocation(top_ramp, move_power-7, 1.8);

    //Move to bottom of ramp
    r.goAndStop(3*PI/4 + 0.03, diagonal_max_speed - 20, 0.6);
    r.waitMoveToLocation(bottom_ramp, move_power-10, 1);

    //Move to before the end
    r.goAndStop(PI/4 - 0.1, max_speed + 20, 0.35);
    r.waitMoveToLocation(before_end, move_power);

    //Turn and move to end
    //r.waitTurnToAngle(PI, turn_power, 0.3);
    r.waitTurnToAngle(PI/2, turn_power + 6.5, 0.3);
    r.waitMoveToLocation(end, max_speed);
}
