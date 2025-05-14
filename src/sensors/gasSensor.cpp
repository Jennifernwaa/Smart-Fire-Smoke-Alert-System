#include "gasSensor.h"
#include "utils/adc.h"
#include "utils/timer.h"
#include <Arduino.h>

// Constants for the gas sensor
#define RL 10.0            // Load resistance in kilo ohms
#define THRESHOLD_RATIO 8.5 // Adjusted threshold for gas detection (RS/R0)

// R0 calibration value for clean air
// This MUST be calibrated for your specific sensor in a clean air environment.
float R0 = 0.75;

// State tracking variable
bool gasDetected = false;

void initGasSensor() {
    // No specific initialization needed for the analog pin besides ADC setup
    Serial.println("Gas sensor initialized.");
}

float readGasRatio() {
    float sensorValueSum = 0;

    // Take multiple readings and average them
    for (int i = 0; i < 100; i++) {

        sensorValueSum += readADC(); 
        delayUs(50); // Adjusted delay for stability
    }
    float sensorValueAvg = sensorValueSum / 100;

    // Convert to voltage (assuming 10-bit ADC with 5V reference)
    float sensorVolt = (sensorValueAvg / 1024.0) * 5.0;

    // Calculate gas sensor resistance (RS)
    float RS_gas = (5.0 - sensorVolt) / sensorVolt;

    // Calculate ratio (RS/R0)
    return RS_gas / R0;
}

void processGasSensor() {
    const int requiredDetections = 3; // Number of consistent detections before triggering
    int detectionCount = 0;

    for (int i = 0; i < requiredDetections; i++) {
        float ratio = readGasRatio();
        Serial.print("Gas Ratio (RS/R0): ");
        Serial.println(ratio);

        if (ratio < THRESHOLD_RATIO) {
            detectionCount++;
        }
        delay(100); // Small delay between checks
    }

    if (detectionCount == requiredDetections) {
        gasDetected = true;
    } else {
        gasDetected = false;
    }
}


bool isGasDetected() {
    return gasDetected;
}