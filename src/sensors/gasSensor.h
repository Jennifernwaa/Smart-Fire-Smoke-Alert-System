#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <Arduino.h>

// Constants for the gas sensor
#define GAS_SENSOR_PIN A0
#define RL 10.0 // Load resistance in kilo ohms
#define CH4_SENSITIVITY 0.4 // Sensitivity for CH4 in ppm
#define CO_SENSITIVITY 0.4 // Sensitivity for CO in ppm
#define LPG_SENSITIVITY 0.4 // Sensitivity for LPG in ppm
#define THRESHOLD_RATIO 0.3  // For medium sensitivity to gas/smoke, high is <0.2, low is >0.4

// Initialize gas sensor
void initGasSensor();

// Read gas concentration ratio (RS/R0)
float readGasConcentration();

// Check if gas level is above threshold
bool isGasDetected();

bool getIsGasDetected(); // Getter function for gasDetected

// Check if the gas sensor has failed
bool isSensorFailed();

// Reset gas sensor state
void resetSensor();

// Process gas sensor reading (call this in main loop)
void processGasSensor();

#endif