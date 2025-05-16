#include "switch.h"
#include <Arduino.h>

void initSwitch() {
    DDRD &= ~(1 << DDD3);   // initialize D3 (pin 18) as input
    PORTD |= (1 << PORTD3); // enable pull up resistor
    EIMSK |= (1 << INT3);   // Enable INT3 interrupt

    EICRA &= ~(1 << ISC31);
    EICRA &= ~(1 << ISC30);
}




