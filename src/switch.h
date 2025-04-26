// switch.h
#ifndef SWITCH_H
#define SWITCH_H

#include <avr/io.h>

// Switch state definitions
#define SWITCH_OPEN 0
#define SWITCH_CLOSED 1

// Initialize switch on PB3
void initSwitch();

// Read the current state of the switch
uint8_t readSwitch();

#endif