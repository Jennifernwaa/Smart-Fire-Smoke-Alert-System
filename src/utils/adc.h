#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void initADC();
uint16_t readADC(uint8_t channel);

#endif
