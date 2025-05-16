#include <avr/io.h>
#include <Arduino.h>
#include "utils/timer.h"

void initFanMosfet() {
    DDRE |= (1 << PE5); // Set PE5 as output
}

void startFan() {
  PORTE |= (1 << PE5); // Drive gate HIGH
}

void stopFan() {
  PORTE &= ~(1 << PE5); // Drive gate LOW
}