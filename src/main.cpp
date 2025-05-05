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
  initBuzzer(); // Initialize the buzzer
  initADC();   // Initialize the Analog-to-Digital Converter
  initLCD();
  updateDisplay("System Initialized", "Monitoring...");

  // Initialize sensors
  initFlameSensor();
  initGasSensor();

  while (1) {
      // Process gas sensor data
      processGasSensor();

      if (isFlameDetected()) {
          alarmActive = 1;
          redLEDOn();
          greenLEDOff();
          startBuzzer();
          updateDisplay("ALARM!", "Flame Detected!");
      } else if (isGasDetected()) {
          alarmActive = 1;
          redLEDOn();
          greenLEDOff();
          startBuzzer();
          updateDisplay("ALARM!", "Gas Detected!");
      } else {
          alarmActive = 0;
          redLEDOff();
          greenLEDOn();
          updateDisplay("No Threat", "Detected");
      }

      delay(1000); // Adjust delay as needed for monitoring frequency
  }

  return 0;
}

// Placeholder for Pin Change Interrupt (if you intend to use it later)
ISR(PCINT0_vect) {
  // Set flag to indicate interrupt occurred
}