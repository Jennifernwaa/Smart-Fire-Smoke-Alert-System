#include "led.h"
#include <avr/io.h>

void initLED() {
    DDRC |= (1 << PC7) | (1 << PC6); // Set PC7 (Pin 30) and PC6 (Pin 31) as output
}

void redLEDOn() {
    PORTC |= (1 << PC7); // Set PC7 high to turn on red LED
}

void redLEDOff() {
    PORTC &= ~(1 << PC7); // Set PC7 low to turn off red LED
}

void greenLEDOn() {
    PORTC |= (1 << PC6); // Set PC6 high to turn on green LED
}

void greenLEDOff() {
    PORTC &= ~(1 << PC6); // Set PC6 low to turn off green LED
}