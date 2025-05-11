#ifndef GSM_H
#define GSM_H

#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); // RX, TX

void sendSMSCommand();
void sendSMS();

#endif