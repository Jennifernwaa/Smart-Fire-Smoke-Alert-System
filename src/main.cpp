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


// #include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


// System state flags
volatile uint8_t alarmActive = 0;
volatile uint8_t systemEnabled = 1;

int main() {

  initLED();
  initPWM();
  initPWMFan();
  initTimer1();
  initTimer0();
  initFlameSensor();

  initLCD();
  moveCursor(0, 0); // moves the cursor to 0, position
  writeString("Testing");

  while (1){
    if (isFlameDetected()) {
        // Flame detected, activate alarm
        alarmActive = 1;
        startBuzzer();
        clearDisplay();
        moveCursor(0, 1); // moves the cursor to 1, position
        writeString("Flame Detected!");
        greenLEDOff();

        moveCursor(0, 0); // moves the cursor to 0, position
        writeString("Red ON");
        redLEDOn();
        delayMs(100);
        redLEDOff();
        delayMs(100);
    } else {
        // No flame detected, deactivate alarm
        alarmActive = 0;
        moveCursor(0, 1); // moves the cursor to 1, position
        writeString("No Flame Detected");
        greenLEDOn();
        moveCursor(0, 0); // moves the cursor to 0, position
        writeString("Green ON");
    }

//bla bla
  }
  return 0;

    
    // Enable global interrupts
    // sei();
    
    // Main loop
    // while (1) {
    //     // Process switch input
    //     if (isSwitchPressed()) {
    //         systemEnabled = !systemEnabled;
            
    //         if (systemEnabled) {
    //             // lcdPrintLine1("System Enabled");
    //             // lcdPrintLine2("Monitoring...");
    //             // ledOn(LED_GREEN);
    //             // buzzerOn();
    //             // _delay_ms(200);
    //             // buzzerOff();
    //         } else {
    //             // lcdPrintLine1("System Disabled");
    //             // lcdPrintLine2("Press to enable");
    //             // ledOff(LED_GREEN);
    //             // buzzerOn();
    //             // _delay_ms(100);
    //             // buzzerOff();
    //             // _delay_ms(100);
    //             // buzzerOn();
    //             // _delay_ms(100);
    //             // buzzerOff();
    //         }
            
    //         // Wait for switch to be released
    //         while (isSwitchPressed()) {
    //             // _delay_ms(10);
    //         }
    //     }
        
    //     // Only process alarms if system is enabled
    //     if (systemEnabled) {
    //         // processAlarms();
    //     } else if (alarmActive) {
    //         // Turn off all alerts if system is disabled
    //         // buzzerOff();
    //         // fanOff();
    //         // ledOff(LED_RED);
    //         // alarmActive = 0;
    //     }
        
    //     // Small delay to prevent CPU hogging
    //     // _delay_ms(100);
    // }
    
    // return 0;
}
// Interrupt Service Routine for Pin Change Interrupt
ISR(PCINT0_vect) {
    // Set flag to indicate interrupt occurred
}
