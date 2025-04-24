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

    // Assuming the flame sensor is connected to PD2
     // Turn on buzzer (assuming buzzer is connected to PB1)

    // Wait before starting the fan
     // Turn on fan (assuming relay is connected to PD3)
     // Keep fan on for some time
        }
