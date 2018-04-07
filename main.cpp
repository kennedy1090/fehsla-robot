#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

#include "tests.h"

//function for getting coordinates manually
Point getCoordinates(char* name, Robot r, bool heading, int number) {
    LCD.Clear();
    LCD.WriteAt(name, 100, 100);
    float x, y;
    Point p;

    //When the screen is touched, save current RPS values and heading to the robot.
    while(!LCD.Touch(&x, &y)){

        //Save the three different headings
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

        //Run the function to get RPS values
        r.updateLocation();
    }

    //Set the values in the struct to the values determined by RPS
    p.x = RPS.X();
    p.y = RPS.Y();

    //Set a small offset for the first value obtained
    if (number == 1)
    {
        p.y = p.y + 0.25;
    }

    //Return the struct Point
    return p;
}

//Start main
int main(void){

    //Declare the RPS points
    Point before_end = {17.5 - 0.5, 21.5};

    Point white_button = {25.8, 20 + 0.7};
    Point white_button_2 = {25.8, 20};

    Point bottom_ramp = {28.5, 21.5};
    Point top_ramp = {30, 41.7};

    Point by_garage_2 = {23.5, 47.8};

    Point grass_ramp = {5, 23};

    //Extra RPS points
    //Point by_start = {17.5, 19};
    //Point by_garage = {16.5, 55};
    //Point by_wheel = {25.9 , 60.4};

    //Set the color boundary and blank heading values
    float colorBoundary = 1;
    float x,y, heading_1, heading_2, heading_3;

    Robot r(true);

    //Touch the screen to take in RPS values and headings
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
    LCD.WriteAt("Ready", 100, 100);
    Sleep(0.2);
    LCD.Clear();

    //Set the motor speeds
    int pulse_angle_speed = 18;
    int pulse_location_speed = 25;

    int turn_power = 42;

    int wrench_power = 43;
    int move_power;

    //If the robot runs on course a-d, lower the speed
    if(RPS.CurrentCourse() == 1)
    {
        move_power = 48;
    }
    else
    {
        move_power = 55;
    }

    int move_power_2 = 70;
    int max_speed = 95;
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
    r.pulse(white_button_2, pulse_location_speed, 0.2);
    r.waitTurnToAngle(PI - 0.05, turn_power, 0.1);
    r.waitFor(0.05);

    //drive into RPS button
    r.goAndStop(PI/2, move_power, 0.27, 1);
    r.waitFor(0.2);

    while(RPS.IsDeadzoneActive() == 0) {
       r.goAndStop(3*PI/2, move_power, 0.27);
       r.pulseAngle(PI - 0.05, pulse_angle_speed, 0.05);
       r.goAndStop(PI/2, move_power, 0.3);
    }

    //Makes sure RPS is on
    while(RPS.IsDeadzoneActive() != 2) {
        r.waitFor(0.1);
    }

    //Back up
    r.goAndStop(3*PI/2, max_speed, 0.12);

    //Hit the correct color button

    //red
    if(r.cds.Value() < colorBoundary) {
        r.goAndStop(PI/4 + 0.04, move_power_2 - 5, 0.557);
        r.goAndStop(3*PI/2, move_power_2, 0.25);

        //Move to jack
        r.waitTurnToAngle(PI, turn_power - 5, 0.1);
        r.goAndStop(0.2, max_speed, 0.65);
    }

    //blue
    else {
        r.goAndStop(3*PI/4, move_power_2 - 5, 0.557);
        r.goAndStop(-PI/4, max_speed, 0.25);

        r.waitFor(0.1);
        //Move a little extra
        r.goAndStop(0, max_speed, 0.39);
        r.waitFor(0.1);

        //Move to jack
        r.waitTurnToAngle(PI, turn_power - 5, 0.1);
        r.goAndStop(0.1, max_speed, 0.63);
    }

    //---------------Jack---------------
    r.wrench.SetDegree(116);

    //Make correct adjustments
    r.goAndStop(PI/2, max_speed, 0.2);

    //Turn to correct angle for Jack
    r.pulseAngle(PI, pulse_angle_speed, 0.05);

    r.waitMoveToLocation(jack_side, move_power, 0.4);
    r.pulse(jack_side, pulse_location_speed, 0.3);
    r.stopAll();

    //Back up while raising the servo angle
    r.wrench.SetDegree(60);
    r.goAndStop(3*PI/2, max_speed, 0.07);

    //---------------Wrench---------------
    r.goAndStop(-PI/4, move_power_2, 0.12);
    r.waitMoveToLocation(wrench, move_power, 0.4);
    r.blindTurn(0, 90, 0.375);
    r.stopAll();
    r.waitFor(0.1);

    r.pulseAngle(heading_1 + PI/2 - 0.03, pulse_angle_speed, 0.04);
    r.wrench.SetDegree(103);
    r.waitFor(0.1);
    r.goAndStop(PI/2, wrench_power, 0.57, 1);
    r.wrench.SetDegree(0);
    r.waitFor(0.1);

    //---------------Grass Ramp---------------
    r.waitMoveToLocation(grass_ramp, move_power - 5, 0.6);
    r.waitTurnToAngle(PI/4, turn_power - 15, 0.06);
    r.moveAtAngle(PI/4 - 0.02, diagonal_max_speed - 30);
    r.waitFor(1.8);

    //---------------Garage---------------
    r.waitMoveToLocation(by_garage, move_power + 10, 1);
    r.pulse(by_garage, pulse_location_speed, 1);

    r.waitTurnToAngle(heading_2 + PI/4 - 0.04, turn_power, 0.06);
    r.goAndStop(PI/2, max_speed - 5, 0.8, 1);
    r.wrench.SetDegree(110);
    r.waitFor(0.45);

    //Back out Diagonally
    r.goAndStop(-PI/4 - 0.25, max_speed, 0.95, 1);
    r.wrench.SetDegree(0);

    //Checks the fuel type
    if(RPS.FuelType() == 1){
        r.wheel.SetDegree(0);
    } else {
        r.wheel.SetDegree(180);
    }

    //---------------Wheel---------------

    //Turns robot to correct angle

    //Move to the wheel
    r.waitMoveToLocation(by_wheel, move_power - 10, 1);
    r.pulse(by_wheel, pulse_location_speed + 5, 0.2);


    //Adjust the angle

    r.blindTurn(1, 90, 0.355);
    r.pulseAngle(heading_3 + 3*PI/4 - 0.035, pulse_angle_speed, 0.03);

    //Run into the fuel pump
    r.goAndStop(-PI/2, move_power + 5, 0.47, 1);

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
    r.goAndStop(3*PI/4 - 0.15, max_speed, 0.5);
    r.waitMoveToLocation(by_garage_2, move_power + 10, 1.9);

    //Move to top of ramp
    r.goAndStop(PI, max_speed, 0.345);
    r.waitMoveToLocation(top_ramp, move_power - 7, 1.9);

    //Move to bottom of ramp
    r.goAndStop(3*PI/4 + 0.03, diagonal_max_speed - 30, 0.9);
    r.waitMoveToLocation(bottom_ramp, move_power-10, 1.5);

    //Move to before the end
    r.goAndStop(PI/4 - 0.1, max_speed + 20, 0.5);
    r.waitMoveToLocation(before_end, move_power + 10, 1.5);

    //Turn and move to end
    r.blindTurn(0, 90, 0.195);
    r.goAndStop(0, max_speed, 2);
}
