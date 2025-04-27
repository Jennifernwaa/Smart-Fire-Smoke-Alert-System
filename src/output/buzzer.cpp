#include "buzzer.h"
#include "utils/timer.h"

#include <avr/io.h>
#include <Arduino.h>


void initBuzzer() {
    // Set PE3 as output
    DDRE |= (1 << PE3);

    // Ensure buzzer is off initially
    PORTE &= ~(1 << PE3);

    // Print initialization message to serial monitor
    Serial.println("Buzzer initialized on pin PE3");
}

void buzzerOn() {
    // Turn buzzer on by setting the pin high
    PORTE |= (1 << PE3);
}

void buzzerOff() {
    // Turn buzzer off by setting the pin low
    PORTE &= ~(1 << PE3);
}

void buzzerToggle() {
    // Toggle buzzer state
    PORTE ^= (1 << PE3);
}

void buzzerBeep(uint16_t duration) {
    // Turn buzzer on
    buzzerOn();
    
    // Wait for specified duration
    for(uint16_t i = 0; i < duration; i++) {
        delayMs(1);
    }
    
    // Turn buzzer off
    buzzerOff();
}

void buzzerAlarmPattern() {
    /// Create an alarm pattern - repeated fast beeps
    for(uint8_t i = 0; i < 3; i++) {
        buzzerOn();
        delayMs(100);
        buzzerOff();
        delayMs(100);
    }
    
    // Brief pause between sets
    delayMs(500);
}