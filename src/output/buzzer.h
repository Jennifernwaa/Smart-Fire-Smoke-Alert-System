#ifndef BUZZER_H
#define BUZZER_H

#include <avr/io.h>

// Function prototypes
void initBuzzer();       // Initialize buzzer pin
void buzzerOn();         // Turn buzzer on
void buzzerOff();        // Turn buzzer off
void buzzerToggle();     // Toggle buzzer state
void buzzerBeep(uint16_t duration);     // Beep for specified duration in ms
void buzzerAlarmPattern(); // Sound an alarm pattern (alternating beeps)

#endif