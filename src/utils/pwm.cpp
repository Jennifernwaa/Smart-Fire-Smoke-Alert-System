#include <avr/io.h>
#include "timer.h"
#include "pwm.h"

// Initialize PWM on Pin no
void initPWM() {

    // Set Fast PWM mode with ICR3 as TOP
    DDRE |= (1 << PE3);             // Set PE3 (OC3A) as output
    TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30); // Fast PWM, non-inverting mode on OC3A
    TCCR3B |= (1 << WGM32) | (1 << CS30);  // Continue Fast PWM, no prescaler


    // Set non-inverted mode for OC3C (Pin 5)
    // Set prescaler to 8 for 2MHz frequency
    // Set the PWM frequency to 1kHz - IDK if this is correct
    OCR3A = 0;  // Initial duty cycle 0
    
}

//Do we need this if udh ada buzzer.cpp??
// Start chirping by cycling through different frequencies
void startBuzzer() {
    OCR3A = 1023; // Set duty cycle (e.g., 5% of ICR3 for a high volume sound)

}
// Stop the buzzer by disabling the PWM output
void stopBuzzer() {
    OCR3A = 0; // Set duty cycle to 0 to stop the buzzer

}
