#include "adc.h"
#include "utils/timer.h"

#include <avr/io.h>

void initADC0()
{
    DDRF &= ~(1 << DDF0);
    PORTF &= ~(1 << PORTF0);
    // Set PF0 (ADC0) as input by clearing the corresponding bit in DDRF
    // Disable the internal pull-up resistor on PF0 (ADC0) by clearing the corresponding bit in PORTF

    ADMUX |= (1 << REFS0);
    // Use AVcc (5V) as the reference voltage

    ADMUX &= ~(1 << REFS1);
    // Make sure REFS1 is cleared to select AVcc reference

    // // Select ADC0 channel (PF0)
    // ADMUX &= 0xF0; // Clear the lower 4 bits of ADMUX to select ADC0

    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Enable ADC and set prescaler to 128 (for 16MHz clock, gives 125KHz ADC clock)
}

unsigned int readADC()
{
    // Start the ADC conversion by setting ADSC (ADC Start Conversion)
    ADCSRA |= (1 << ADSC);

    // This is a blocking wait, so the program will pause here until the conversion is done
    while (ADCSRA & (1 << ADSC));

    // Return the 10-bit ADC result
    return ADC;
}

