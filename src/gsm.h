#ifndef GSM_H
#define GSM_H

#include <SoftwareSerial.h>

extern SoftwareSerial SIM900; // Declare the SIM900 object as external

void sendSMS();

#endif
