#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <stdint.h> // For uint16_t
#include <avr/io.h>

// Function declarations
void initGasSensor();
uint16_t readGasSensor();
bool isGasDetected(uint16_t threshold);
void monitorGasLevels(uint16_t threshold);

#endif // GAS_SENSOR_H