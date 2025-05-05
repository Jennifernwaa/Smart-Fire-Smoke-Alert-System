#include <Arduino.h>

#include "utils/adc.h"
#include "utils/pwm.h"
#include "utils/timer.h"

#include "sensors/flameSensor.h"
#include "sensors/gasSensor.h"

// #include "gsm.h"
// #include "switch.h"

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
  initGasSensor(); // Initialize the gas sensor

  initLCD();
  moveCursor(0, 0); // moves the cursor to 0, position
  writeString("Monitoring...");

  while (1){
    if (isFlameDetected()) {
        // Flame detected, activate alarm
        alarmActive = 1;
        startBuzzer();
        clearDisplay();
        moveCursor(0, 1); // moves the cursor to the second line
        writeString("Flame Detected!");
        greenLEDOff();
        redLEDOn();
    } else if (getIsGasDetected()) { // Check the gas sensor status
        // Gas detected, activate alarm
        alarmActive = 1;
        startBuzzer();
        clearDisplay();
        moveCursor(0, 1); // moves the cursor to the second line
        writeString("Gas Detected!");
        greenLEDOff();
        redLEDOn();
    }
     else {
        // No flame or gas detected, deactivate alarm
        alarmActive = 0;
        stopBuzzer();
        clearDisplay();
        moveCursor(0, 1); // moves the cursor to the second line
        writeString("No Threat");
        greenLEDOn();
    }

    delay(100); // Small delay for stability
  }
  return 0;
}

// Interrupt Service Routine for Pin Change Interrupt (if used elsewhere)
// ISR(PCINT0_vect) {
//     // Handle pin change interrupt
// }