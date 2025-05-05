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

    float sensor_volt;
    float RS_air; //  Get the value of RS via in a clear air
    float R0;  // Get the value of R0 via in LPG
    float sensorValue;

    /*--- Get a average data by testing 100 times ---*/
    for(int x = 0 ; x < 100 ; x++)
    {
        sensorValue = sensorValue + analogRead(A0);
    }
    sensorValue = sensorValue/100.0;
    /*-----------------------------------------------*/

    sensor_volt = sensorValue/1024*5.0;
    RS_air = (5.0-sensor_volt)/sensor_volt; // omit *RL
    R0 = RS_air/9.9; // The ratio of RS/R0 is 9.9 in LPG gas from Graph (Found using WebPlotDigitizer)

    Serial.print("sensor_volt = ");
    Serial.print(sensor_volt);
    Serial.println("V");

    Serial.print("R0 = ");
    Serial.println(R0);
    delay(1000);
      // Process gas sensor data
      // processGasSensor();

      // if (isFlameDetected()) {
      //     alarmActive = 1;
      //     redLEDOn();
      //     greenLEDOff();
      //     startBuzzer();
      //     updateDisplay("ALARM!", "Flame Detected!");
      // } else if (isGasDetected()) {
      //     alarmActive = 1;
      //     redLEDOn();
      //     greenLEDOff();
      //     startBuzzer();
      //     updateDisplay("ALARM!", "Gas Detected!");
      // } else {
      //     alarmActive = 0;
      //     redLEDOff();
      //     greenLEDOn();
      //     updateDisplay("No Threat", "Detected");
      // }

      // delay(1000); // Adjust delay as needed for monitoring frequency
  }

  return 0;
}

// Placeholder for Pin Change Interrupt (if you intend to use it later)
ISR(PCINT0_vect) {
  // Set flag to indicate interrupt occurred
}