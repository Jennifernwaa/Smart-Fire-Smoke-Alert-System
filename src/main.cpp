#include <Arduino.h>

#include "utils/adc.h"
#include "utils/pwm.h"
#include "utils/timer.h"
#include "output/fan.h"
#include "sensors/flame_sensor.h"
#include "sensors/gas_sensor.h"
#include "gsm.h"
#include "output/lcd.h"
#include "output/led.h"
#include "output/buzzer.h"
#include "switch.h"


#include <avr/io.h>
#include <avr/interrupt.h>

int main() {
    // Initialize peripherals


    sei();

    while (1) {

    }
}
