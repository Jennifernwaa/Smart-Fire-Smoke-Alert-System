#include "flameSensor.h"
#include <avr/io.h>

void initFlameSensor() {
    DDRH &= ~(1 << PH3); // Set PH3 (Pin 6) as input
}

// bool isFlameDetected() {
//     // Read the state of the flame sensor pin
//     return (PINH & (1 << PH3)) == 0; // Active low, so check if the pin is low
// }

bool isFlameDetected() {
    // Read the state of the flame sensor pin
    if (!(PINH & (1 << PH3))) { // Active low, so check if the pin is low
        return true; // Flame detected
    } else {
        return false; // No flame detected
    }
}