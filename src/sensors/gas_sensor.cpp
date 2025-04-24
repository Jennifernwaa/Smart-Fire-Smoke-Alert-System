#include <avr/io.h>
#include <util/delay.h>
#include "output/buzzer.h"
#include "utils/adc.h"
#include <Arduino.h> // Include Arduino library for Serial communication

// Constants for calibration (example values, replace with actual calibration data)
const float RL = 20.0; // Load resistance in kΩ
const float R0 = 10.0; // Sensor resistance in clean air (calibrate this value)
const float CH4_Sensitivity = 0.5; // Sensitivity factor for CH4 (example)



// Initialize the gas sensor
void initGasSensor() {
  // Configure the ADC (Analog-to-Digital Converter) for the gas sensor
  // Set reference voltage to AVcc
  ADMUX = (1 << REFS0); // Reference voltage set to AVcc

  // Set ADC prescaler to 128 for 16MHz clock (to ensure ADC clock is between 50kHz and 200kHz)
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Enable the ADC
  ADCSRA |= (1 << ADEN);

  // Configure A0 pin as input (default state for ADC pins)
  DDRC &= ~(1 << PF0); // PF0 corresponds to A0 pin
}

// Read the gas sensor value
uint16_t readGasSensor() {
  ADMUX = (ADMUX & 0xF0) | (0 & 0x0F); // Select ADC0 channel
  ADCSRA |= (1 << ADSC); // Start ADC conversion
  while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
  return ADC;

  uint16_t adcValue = readADC(0); 
  float voltage = (adcValue / 1023.0) * 5.0;
  float Rs = (5.0 - voltage) * RL / voltage;
  float ratio = Rs / R0;
  float ppm = ratio / CH4_Sensitivity;
  return ppm;
}


int main(){


  // Initialize the gas sensor
  initGasSensor();

  // Set up serial communication for debugging
  Serial.begin(9600);

  float sensor_volt;
  float RS_air;
  float R0;
  float sensorValue = 0;

  while (1) {
    for (int x = 0; x < 100; x++) {
      sensorValue += analogRead(A0);  // A0 connected to MQ9 AO
    }
    sensorValue /= 100.0;
  
    sensor_volt = (sensorValue / 1024.0) * 5.0;
    RS_air = (5.0 - sensor_volt) / sensor_volt;
    R0 = RS_air / 9.9; // Based on MQ9 datasheet
  
    Serial.print("sensor_volt = ");
    Serial.print(sensor_volt);
    Serial.println(" V");
  
    Serial.print("R0 = ");
    Serial.println(R0);
  

    // Delay for a second before the next reading
    delay(1000);
  }
  return 0;
}