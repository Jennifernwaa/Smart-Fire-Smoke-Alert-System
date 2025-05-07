#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <Arduino.h>

// Constants for the gas sensor
#define GAS_SENSOR_PIN A0


// Initialize gas sensor
void initGasSensor();

float readGasRatio();  

void processGasSensor();    

bool isGasDetected(); // Check if gas is detected   

#endif