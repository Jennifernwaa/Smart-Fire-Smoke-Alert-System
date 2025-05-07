#include "gasSensor.h"
#include "utils/adc.h"
#include "utils/timer.h"
#include <Arduino.h>

// Constants for the gas sensor
#define RL 10.0            // Load resistance in kilo ohms
#define THRESHOLD_RATIO 100 // Adjusted threshold for gas detection (RS/R0)

// R0 calibration value for clean air
// This MUST be calibrated for your specific sensor in a clean air environment.
float R0 = 1.03;

// State tracking variable
bool gasDetected = false;

void initGasSensor() {
    // No specific initialization needed for the analog pin besides ADC setup
    Serial.println("Gas sensor initialized.");
}

float readGasRatio() {
    float sensorValueSum = 0;
    int numReadings = 50; // Reduced number of readings for efficiency

    // Take multiple readings and average them
    for (int i = 0; i < numReadings; i++) {
        sensorValueSum += readADC();
        delayUs(50); // Adjusted delay for stability
    }
    float sensorValueAvg = sensorValueSum / numReadings;

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

bool isGasDetected() {
    return gasDetected;
}