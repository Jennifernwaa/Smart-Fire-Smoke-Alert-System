#ifndef FLAME_SENSOR_H
#define FLAME_SENSOR_H

#include <avr/io.h>

// Initialize the pins for the flame sensor
void initializeFlameSensor();

// Check if flame is detected
bool isFlameDetected();

// Placeholder function for handling flame detection
void handleFlameDetection();

#endif // FLAME_SENSOR_H