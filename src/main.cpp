#include <Arduino.h>

#include "utils/adc.h"
#include "utils/pwm.h"
#include "utils/timer.h"

#include "sensors/flameSensor.h"
#include "sensors/gasSensor.h"

#include "gsm.h"
#include "switch.h"


#include "output/lcd.h"
#include "output/led.h"
#include "output/fan.h"


// #include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Enum for states of the button press state machine
typedef enum {
    wait_press,        // Waiting for button press
    debounce_press,    // Debouncing after press
    wait_release,      // Waiting for button release
    debounce_release,  // Debouncing after release
} current_state;

volatile current_state state = wait_press; // Start in waiting-for-press state

// Alarm state
enum AlarmState { ALARM_OFF, ALARM_ON };
AlarmState alarmState = ALARM_OFF; // Initialize alarmState to ALARM_OFF (buzzer off)

// System state flags
volatile uint8_t alarmActive = 0;
volatile uint8_t systemEnabled = 1;

void updateDisplay(const char* line1, const char* line2) {
    clearDisplay();
    moveCursor(0, 0);
    writeString(line1);
    moveCursor(0, 1);
    writeString(line2);
}

int main() {
    // Initialize essential peripherals
    initLED();
    initPWMFan(); // Initialize PWM for fan control
    initPWM();   // Initialize PWM for buzzer controlin
    initTimer0(); // Initialize Timer0 for timing functions
    initTimer1(); // Initialize Timer1 for timing functions
    initADC();   // Initialize the Analog-to-Digital Converter
    initSwitch(); // Initialize the switch for button press
    initLCD(); // Initialize the LCD display
    initFanMosfet(); // Initialize the fan MOSFET control

    Serial.begin(9600); // Initialize serial communication for debugging
    Serial.println("System Starting...");

    clearDisplay();
    moveCursor(0, 0);
    writeString("Hello");

    // Initialize sensors
    initFlameSensor();
    initGasSensor();
    sei(); // Enable global interrupts

    while (1) {
        if (state != wait_press) { // make sure button is debounced
            Serial.println("Button state changed.");
            state = wait_press;
            delayMs(50);
            Serial.println("Button Pressed");
        }
        // Process gas sensor data
        processGasSensor();

        if (isFlameDetected() || isGasDetected()) {
            alarmActive = 1;
            startBuzzer();
            clearDisplay();
            greenLEDOff();
            toggleRedLED();
            startFan();
            // matiin sendSMS before actually serious demo!!
            if (isFlameDetected() && isGasDetected()) {
                Serial.println("Flame and Gas Detected!");
                updateDisplay("ALARM!", "Flame & Gas!"); // still need changes on the display
                sendSMS(); // Call the sendSMS function when an alarm occurs
            } else if (isFlameDetected()) {
                Serial.println("Flame Detected!");
                updateDisplay("Red ON", "Flame Detected!");
                sendSMS(); // Call the sendSMS function when an alarm occurs
            } else {
                Serial.println("Gas Detected!");
                updateDisplay("Red ON", "Gas Detected!");
                sendSMS(); // Call the sendSMS function when an alarm occurs
            } 
            // else {
            //     Serial.println("No Gas Detected!");
            //     updateDisplay("Red ON", "Flame Detected!"); // still need changes on the display
            //     sendSMS(); // Call the sendSMS function when an alarm occurs
            // }
        } else {
            alarmActive = 0;
            greenLEDOn(); 
            updateDisplay("Safe", "Nothing Detected");
            Serial.println("No Threat Detected");
        }
        delay(1000); // Adjust delay as needed for monitoring frequency
    }
    
    return 0;
}

ISR(INT3_vect){
    state = wait_release; // change the state of button
    stopBuzzer();                    // turn off the buzzer
    stopFan();                       // turn off the fan
    redLEDOff();                    // turn off the red LED
    greenLEDOn();                  // turn on the green LED

    updateDisplay("System", "Deactivated");
    alarmState = ALARM_OFF; // change the alarm state to false (turning off the buzzer)
    alarmActive = 0;        // Reset alarm active flag

    // Update the LCD display to show the system is reset
    updateDisplay("System Reset", "Monitoring...");

    // Debounce the button
    delayMs(100);
}