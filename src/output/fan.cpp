#include <avr/io.h>
#include <Arduino.h>
#include "timer.h"


void initFanMosfet() {
    DDRE |= (1 << PE5); // Set PE5 as output
}

void startFan() {
  PORTE |= (1 << PE5); // Drive gate HIGH
}

void stopFan() {
  PORTE &= ~(1 << PE5); // Drive gate LOW
}

void setup() {
    initFanMosfet();
    Serial.begin(9600);
}

void loop() {
  startFan();
  Serial.println("Starting Fan");

  delayMs(5000);


  stopFan();
  Serial.println("Stopping Fan");

  delayMs(5000);
}