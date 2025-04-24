#include <avr/io.h>
#include "timer.h"
#include "pwm.h"

// Initialize PWM on Pin no
void initPWM() {
    // Set pin as output


    // Set Fast PWM mode with ICR3 as TOP
    // Set non-inverted mode for OC3C (Pin 5)
    // Set prescaler to 8 for 2MHz frequency
    // Set the PWM frequency to 1kHz - IDK if this is correct
    
}


//Do we need this if udh ada buzzer.cpp??
// Start chirping by cycling through different frequencies
void startBuzzer() {
    for (uint8_t i = 0; i < 3; i++) {
        setBuzzerFrequency(2000); // High tone
        delayMs(100);
        setBuzzerFrequency(1000); // Low tone
        delayMs(100);
    }
}

// Stop the buzzer by disabling the PWM output
void stopBuzzer() {
    setBuzzerFrequency(0);
}
