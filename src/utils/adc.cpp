#include "adc.h"
#include "utils/timer.h"

#include <avr/io.h>

void initADC() // Renamed to a more general initADC as you might use other ADC channels later
{
    // Initialize ADC0 (connected to PF0/A0)
    DDRF &= ~(1 << DDF0);
    PORTF &= ~(1 << PORTF0);
    // Set PF0 (ADC0) as input and disable pull-up

    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);
    // Use AVcc as reference

    // Select ADC0 channel (PF0). The lower 4 bits of ADMUX control the channel.
    ADMUX &= 0xF0; // Clear any previous channel selection
    ADMUX |= 0x00; // Select ADC0 (0b0000)

    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Enable ADC and set prescaler to 128
}

unsigned int readADC()
{
    // Start the ADC conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC));

    // Return the ADC result
    return ADC;
}