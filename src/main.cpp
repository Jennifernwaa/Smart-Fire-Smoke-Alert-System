#include <Arduino.h>

#include "utils/adc.h"
#include "utils/pwm.h"
#include "utils/timer.h"

#include "sensors/flameSensor.h"
#include "sensors/gasSensor.h"

#include "switch.h"

#include "output/lcd.h"
#include "output/led.h"
#include "output/fan.h"

#include "gsm.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>

// Enum for states of the button press state machine
typedef enum {
    wait_press,        // Waiting for button press
    debounce_press,    // Debouncing after press
    wait_release,      // Waiting for button release
    debounce_release,  // Debouncing after release
} current_state;

volatile current_state state = wait_press; // Start in waiting-for-press state

volatile uint8_t sendingSMS = 0;       // Flag to indicate if SMS is being sent
volatile uint8_t flameDetected = 0;    // Flag for flame detection
volatile uint8_t gasDetectedFlag = 0;  // Flag for gas detection

// Alarm state
enum AlarmState { ALARM_OFF, ALARM_ON };
AlarmState alarmState = ALARM_OFF; // Initialize alarmState to ALARM_OFF (buzzer off)

// System state flags
volatile uint8_t alarmActive = 0;   // Flag to indicate if alarm is active
volatile uint8_t systemEnabled = 1; // Flag to indicate if system is enabled
uint8_t alertTriggered = 0;         // Flag to indicate if alert has been triggered

// Helper function to update the LCD display with two lines
void updateDisplay(const char* line1, const char* line2) {
    clearDisplay();
    moveCursor(0, 0);
    writeString(line1);
    moveCursor(0, 1);
    writeString(line2);
}

int main() {
    Serial.begin(9600);      // Initialize serial communication
    initLED();               // Initialize LEDs
    initPWM();               // Initialize PWM
    initTimer0();            // Initialize Timer0
    initTimer1();            // Initialize Timer1
    initADC();               // Initialize ADC
    initLCD();               // Initialize LCD
    initFanMosfet();         // Initialize fan MOSFET
    initGSM();               // Initialize GSM module
    initFlameSensor();       // Initialize flame sensor
    initGasSensor();         // Initialize gas sensor

    clearDisplay();          // Clear LCD display
    moveCursor(0, 0);
    writeString("Hello");    // Display welcome message
    sei();                   // Enable global interrupts

    while (1) {
        // Handle button state machine (debouncing)
        if (state != wait_press) { // make sure button is debounced
            Serial.println("Button state changed.");
            state = wait_press;
            delayMs(50);
            Serial.println("Button Pressed");
        }

        // Main monitoring logic
        if (!alertTriggered) {
            // Check for flame detection if not already detected
            if (!flameDetected) flameDetected = isFlameDetected();
            // Check for gas detection if not already detected
            if (!gasDetectedFlag) {
                processGasSensor();
                gasDetectedFlag = isGasDetected();
            }

            // If flame or gas is detected, trigger alert
            if (isFlameDetected() || isGasDetected()) {
                alertTriggered = 1;
                startBuzzer();      // Turn on buzzer
                clearDisplay();     // Clear LCD
                greenLEDOff();      // Turn off green LED
                toggleRedLED();     // Toggle red LED
                startFan();         // Turn on fan

                // Display appropriate message and send SMS
                if (isFlameDetected() && isGasDetected()) {
                    Serial.println("Flame and Gas Detected!");
                    updateDisplay("ALARM!", "Flame & Gas!");
                    delayMs(1000);
                    sendSMS();
                } else if (isFlameDetected()) {
                    Serial.println("Flame Detected!");
                    updateDisplay("Red ON", "Flame Detected!");
                    delayMs(1000);
                    sendSMS();
                } else {
                    Serial.println("Gas Detected!");
                    updateDisplay("Red ON", "Gas Detected!");
                    delayMs(1000);
                    sendSMS();
                }
            } else {
                // No threat detected, system is safe
                greenLEDOn(); // Turn on green LED
                updateDisplay("Safe", "Nothing Detected");
                Serial.println("No Threat Detected");
            }
        }
        delayMs(100); // Small delay for loop
    }
}

// External interrupt service routine for button press (e.g., system reset)
ISR(INT3_vect){
    state = wait_release; // Change the state of button
    stopBuzzer();         // Turn off the buzzer
    stopFan();            // Turn off the fan
    redLEDOff();          // Turn off the red LED
    greenLEDOn();         // Turn on the green LED

    updateDisplay("System", "Deactivated"); // Show deactivated message
    alarmState = ALARM_OFF; // Change the alarm state to false (turning off the buzzer)
    alarmActive = 0;        // Reset alarm active flag

    // Update the LCD display to show the system is reset
    updateDisplay("System Reset", "Monitoring...");

    // Debounce the button
    delayMs(100);
}
