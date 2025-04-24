#ifndef FAN_H
#define FAN_H
#include <avr/io.h>
#include <stdint.h>

void initializeFan();
void turnOnFan();
void turnOffFan();
void setFanSpeed(int speed);


#endif // FAN_H