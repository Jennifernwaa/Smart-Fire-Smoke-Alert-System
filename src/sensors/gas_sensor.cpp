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

int main() {
  initGasSensor();
  Serial.begin(9600); // Initialize the Serial communication

  while (1) {
    float gasPPM = readGasSensor();
    if (gasPPM > 200) {
      Serial.print("Gas concentration: ");
      Serial.print(gasPPM, 5); // Print gasPPM with 5 decimal places
      Serial.println(" ppm");
    } else {
      Serial.print("Gas concentration: ppm less than 200");
    }
    _delay_ms(1000);
  }
}

