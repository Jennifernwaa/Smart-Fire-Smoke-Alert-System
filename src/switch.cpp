// switch.cpp
#include "switch.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitch() {
    DDRD &= ~(1 << DDD3);   // initialize D3 (pin 18) as input
    PORTD |= (1 << PORTD3); // enable pull up resistor
    EIMSK |= (1 << INT3);   // Enable INT3 interrupt

    //add comment for this
    EICRA &= ~(1 << ISC31);
    EICRA &= ~(1 << ISC30);
}




