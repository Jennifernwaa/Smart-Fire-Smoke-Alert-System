#include <Arduino.h>

#include "utils/adc.h"
#include "utils/pwm.h"
#include "utils/timer.h"

#include "sensors/flameSensor.h"
#include "sensors/gasSensor.h"

#include "gsm.h"
#include "switch.h"

#include "output/lcd.h"
#include "output/buzzer.h"
#include "output/fan.h"
#include "output/led.h"


#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


// System state flags
volatile uint8_t alarmActive = 0;
volatile uint8_t systemEnabled = 1;

void processAlarms() {
    // Check gas sensor
    if (isGasDetected()) {
        alarmActive = 1;
        
        // Activate buzzer


        // Turn on fan
        
        // Display warning on LCD
        
        // Turn on warning LED
        
        // Send SMS alert
    }
    
    // Check flame sensor
    if (isFlameDetected()) {
        alarmActive = 1;
        
        // Activate buzzer

        
        // Display warning on LCD
        
        // Turn on warning LED
        
        // Send SMS alert
    }
    
    // If no alarms and the system was previously in alarm state
    if (!isGasDetected() && !isFlameDetected() && alarmActive) {
        alarmActive = 0;
        
        // Turn off buzzer
        
        // Turn off fan
        
        // Update LCD
        
        // Turn off warning LED
    }
}

void initSystem() {
    // Initialize serial communication
    Serial.begin(9600);
    Serial.println("Smart Fire and Smoke Alert System");
    
    // Initialize ADC for gas sensor
    
    // Initialize gas sensor
    
    // Initialize flame sensor
    
    // Initialize outputs
    
    // Initialize GSM module

    
    // Initialize switch

    
    // Initialize timers
    
    // Display startup message
    
    // Turn on status LED

    
    // Beep to indicate system is ready
}

int main() {
    // Initialize the system
    initSystem();
    
    // Enable global interrupts
    sei();
    
    // Main loop
    while (1) {
        // Process switch input
        if (isSwitchPressed()) {
            systemEnabled = !systemEnabled;
            
            if (systemEnabled) {
                // lcdPrintLine1("System Enabled");
                // lcdPrintLine2("Monitoring...");
                // ledOn(LED_GREEN);
                // buzzerOn();
                // _delay_ms(200);
                // buzzerOff();
            } else {
                // lcdPrintLine1("System Disabled");
                // lcdPrintLine2("Press to enable");
                // ledOff(LED_GREEN);
                // buzzerOn();
                // _delay_ms(100);
                // buzzerOff();
                // _delay_ms(100);
                // buzzerOn();
                // _delay_ms(100);
                // buzzerOff();
            }
            
            // Wait for switch to be released
            while (isSwitchPressed()) {
                // _delay_ms(10);
            }
        }
        
        // Only process alarms if system is enabled
        if (systemEnabled) {
            // processAlarms();
        } else if (alarmActive) {
            // Turn off all alerts if system is disabled
            // buzzerOff();
            // fanOff();
            // ledOff(LED_RED);
            // alarmActive = 0;
        }
        
        // Small delay to prevent CPU hogging
        // _delay_ms(100);
    }
    
    return 0;
}
// Interrupt Service Routine for Pin Change Interrupt
ISR(PCINT0_vect) {
    // Set flag to indicate interrupt occurred
}
