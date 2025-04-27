#include "fan.h"
#include <avr/io.h>


//initialize the pins for the Fan
void initializeFan(){
// Set FAN_PIN (PH5) as output
  DDRH |= (1 << PH5);
  // Ensure fan is off initially
  PORTH &= ~(1 << PH5);
  
  // Set FAN_PWM_PIN (PH6) as output for PWM control
  DDRH |= (1 << PH6);
  // Initialize Timer2 for PWM on pin 9
  // Using Phase Correct PWM mode
  TCCR2A = (1 << COM2B1) | (1 << WGM20);  // Phase Correct PWM mode
  TCCR2B = (1 << CS22);  // Prescaler of 64
  OCR2B = 0;  // Initially 0% duty cycle (fan off)
  
  Serial.println("Fan initialized on pin 8 with PWM control on pin 9");

}

/**
 * Turn on the fan at full speed
 */
void turnOnFan() {
    // Set the pin to high
    PORTH |= (1 << PH5);
    // Set full speed on PWM
    OCR2B = 255;
    
    Serial.println("Fan turned ON");
  }

/**
 * Turn off the fan
 */
void turnOffFan() {
    // Set the pin to low
    PORTH &= ~(1 << PH5);
    // Set PWM to 0
    OCR2B = 0;
    
    Serial.println("Fan turned OFF");
  }


//if we need pwm then use this, if not just delete this function
//set the fan speed ????
void setFanSpeed(int speed){
    //set the speed of the fan using PWM
    if (speed > 0) {
      // Ensure main power pin is on
      PORTH |= (1 << PH5);
      // Set PWM duty cycle
      OCR2B = speed;
      
      Serial.print("Fan speed set to: ");
      Serial.println(speed);
    } else {
      turnOffFan();
    }
}

  