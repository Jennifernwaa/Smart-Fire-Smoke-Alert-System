// gsm.h
#ifndef GSM_H
#define GSM_H

#include <stdint.h>

// GSM module initialization
void initGSM();

// Send SMS alert
void sendSMSAlert(const char* message);

// Send SMS to specific number
void sendSMS(const char* phoneNumber, const char* message);

// Check if GSM module is ready
bool isGSMReady();

// Make a call to a specific number (for urgent alerts)
void makeCall(const char* phoneNumber);

// Process any incoming SMS messages
void processGSMMessages();

#endif // GSM_H