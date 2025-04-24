#ifndef FLAME_SENSOR_H
#define FLAME_SENSOR_H

#include <avr/io.h>


void initializeFlameSensor();
void flameDetectedLoop();

#endif // FLAME_SENSOR_H