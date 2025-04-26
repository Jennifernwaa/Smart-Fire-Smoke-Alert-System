#include "led.h"
#include <avr/io.h>

void initLED() {
    DDRE |= (1 << PE4) | (1 << PE5); // Set PE4 (Pin 2) and PE5 (Pin 3) as output
}

void redLEDOn() {
    PORTE |= (1 << PE4); // Set PE4 high to turn on red LED
}

void redLEDOff() {
    PORTE &= ~(1 << PE4); // Set PE4 low to turn off red LED
}

void greenLEDOn() {
    PORTE |= (1 << PE5); // Set PE5 high to turn on green LED
}

void greenLEDOff() {
    PORTE &= ~(1 << PE5); // Set PE5 low to turn off green LED
}