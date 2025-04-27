#ifndef FAN_H
#define FAN_H

#include <avr/io.h>

void initializeFan();
void turnOnFan();
void turnOffFan();
void setFanSpeed(int speed);

#endif