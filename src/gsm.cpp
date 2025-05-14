#include "gsm.h"
#include "utils/timer.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

// Define the actual SIM900 object here (only once)
SoftwareSerial SIM900(7, 8);

void sendSMS() {
    SIM900.print("AT+CMGF=1\r"); 
    delayMs(100);

    // Send SMS to recipient
    SIM900.println("AT+CMGS=\"+6287842066617\""); 
    delayMs(100);

    SIM900.println("ALERT: Fire or smoke detected at your premises. Please take immediate action. - Smart Alert System");
    delayMs(100);

    // Send the SMS (ASCII code 26 for ^Z)
    SIM900.println((char)26); 
    delayMs(5000); 
}
