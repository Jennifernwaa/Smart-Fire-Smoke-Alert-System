// switch.cpp
#include "switch.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Debounce delay in milliseconds
#define DEBOUNCE_DELAY 50

// Volatile flag to indicate switch state change
volatile uint8_t switchStateChanged = 0;

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitch() {
    // Initialize the switch as input
     // Set Pin as input
    
    // Enable the internal pull-up resistor on Pin


    // Enable pin change interrupt for PCINT of the Pin (Pin)
    // Enable PCINT0 interrupt group
    // Enable interrupt for Pin
}

// Read the current state of the switch
uint8_t readSwitch() {
    // If using INPUT_PULLUP, the logic is inverted (LOW means pressed)
    return (PINB & (1 << PINB3)) ? SWITCH_OPEN : SWITCH_CLOSED; //ganti pin number
}



