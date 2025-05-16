#include <SoftwareSerial.h>
#include <Arduino.h>

// Configure software serial port
SoftwareSerial SIM900(7, 8); 

void sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  SIM900.println("AT+CMGS=\"+6287842066617\""); 
  delay(100);
  
  SIM900.println("FIRE AND SMOKE DETECTED!"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}

void initGSM() {
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  SIM900.begin(19200);
  delay(20000);   
  // Send the SMS
  sendSMS();
}