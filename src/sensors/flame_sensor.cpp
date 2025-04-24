#include "flame_sensor.h"
#include <avr/io.h>

void initializeFlameSensor() {
    // Configure the appropriate pin as input for the flame sensor
    // Example: DDRx &= ~(1 << PINx); // Replace x with the appropriate port and pin
}

void flameDetectedLoop() {
    // Read the pin connected to the flame sensor
    // Example: return (PINx & (1 << PINx)); // Replace x with the appropriate port and pin
    // Placeholder, replace with actual implementation

    if (!(PIND & (1 << PIND2))) { // Assuming the flame sensor is connected to PD2
        PORTB |= (1 << PORTB1); // Turn on buzzer (assuming buzzer is connected to PB1)

        if (millis() - previousTime > SPRINKLER_START_DELAY) { // Wait before starting the fan
            PORTD &= ~(1 << PORTD3); // Turn on fan (assuming relay is connected to PD3)
            _delay_ms(SPRINKLER_ON_TIME); // Keep fan on for some time
        }
    } else {
        PORTB &= ~(1 << PORTB1); // Turn off buzzer
        PORTD |= (1 << PORTD3);  // Turn off sprinkler
        previousTime = millis(); // Reset the timer
    }
}
