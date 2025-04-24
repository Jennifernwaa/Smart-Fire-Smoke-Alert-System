#include "fan.h"
#include <avr/io.h>


//initialize the pins for the Fan
void initializeFan(){

}

//turn on the fan
void turnOnFan(){
    //set the pin to high

}

//turn off the fan
void turnOffFan(){
    //set the pin to low

}
//set the fan speed ????
void setFanSpeed(int speed){
    //set the speed of the fan
    //this is a placeholder function, you will need to implement this based on your hardware
    //for example, you might use PWM to control the speed of the fan
    //or you might use a DAC to set the voltage to the fan
    //or you might use a simple on/off control
    //this is up to you and your hardware design

    //for now, we will just turn the fan on or off based on the speed
    if(speed > 0){
        turnOnFan();
    } else {
        turnOffFan();
    }
}
