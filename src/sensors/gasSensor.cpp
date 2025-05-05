#include "utils/timer.h"
#include "utils/adc.h"
#include "gasSensor.h"

#include <Arduino.h>
#include <avr/io.h>

// Constants for the gas sensor
#define RL 10.0            // Load resistance in kilo ohms
#define THRESHOLD_RATIO 0.1 // Threshold for gas detection (RS/R0)
#define NUM_READINGS 100    // Number of readings to average

// R0 calibration value for clean air
// This should be calibrated based on your specific sensor
float R0 = 0.85;

// State tracking variable
bool gasDetected = false;

void initGasSensor() {
    // Initialize gasDetected state
    gasDetected = false;
    Serial.println("Gas sensor initialized");
}

float readGasRatio() {
    float sensorValueSum = 0;

    // Take multiple readings and average them
    for (int i = 0; i < NUM_READINGS; i++) {
        sensorValueSum += readADC();
        delayUs(10); // Short delay between readings for stability
    }
    float sensorValueAvg = sensorValueSum / NUM_READINGS;

    // Convert to voltage (assuming 10-bit ADC with 5V reference)
    float sensorVolt = (sensorValueAvg / 1023.0) * 5.0;

    // Calculate gas sensor resistance (RS)
    float RS_gas = (5.0 - sensorVolt) * RL / sensorVolt;

    // Calculate ratio (RS/R0)
    return RS_gas / R0;
}

void processGasSensor() {
    float ratio = readGasRatio();
    Serial.print("Gas Ratio (RS/R0): ");
    Serial.println(ratio);

    // Check if gas concentration exceeds threshold
    if (ratio < THRESHOLD_RATIO) {
        gasDetected = true;
        Serial.println("Gas detected!");
    } else {
        gasDetected = false;
        Serial.println("No gas detected.");
    }
}

bool getIsGasDetected() {
    return gasDetected;
}