#include <avr/io.h>
#include <util/delay.h>
#include "output/buzzer.h"
#include "utils/adc.h"
#include <Arduino.h> // Include Arduino library for Serial communication

// Constants for the gas sensor
#define RL 10.0 // Load resistance in kilo ohms
#define CH4_Sensitivity 0.4 // Sensitivity for CH4 in ppm
#define CO_Sensitivity 0.4 // Sensitivity for CO in ppm
#define LPG_Sensitivity 0.4 // Sensitivity for LPG in ppm
#define THRESHOLD_RATIO 0.3  // For medium sensitivity to gas/smoke, high is <0.2, low is >0.4


float R0 = 0.85; //edit later again based on priskas answer

float readGasConcentration() {
  float sensorValue = 0;
  for (int i = 0; i < 100; i++) {
    sensorValue += analogRead(A0); //readADC maybe?
  }
  sensorValue /= 100.0;

  float sensorVolt = (sensorValue / 1024.0) * 5.0;
  float RS_gas = (5.0 - sensorVolt) * RL / sensorVolt;
  float ratio = RS_gas / R0;

  return ratio;
}

void gasLoop() {
  while (1) {
    float ratio = readGasConcentration();

    Serial.print("Gas Ratio (RS/R0): ");
    Serial.print(ratio);
    Serial.print("\r\n");

    if (ratio < THRESHOLD_RATIO) {
      // buzzerOn(); turn buzzer on
      Serial.print("Dangerous gas detected!\r\n");
    } else {
      // buzzerOff(); turn buzzer off
      Serial.print("Air quality normal.\r\n");
    }

    // delayMs(1000); // 1 second delay
  }
}