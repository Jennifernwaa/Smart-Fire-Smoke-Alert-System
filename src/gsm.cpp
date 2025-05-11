#include "gsm.h"
#include "utils/timer.h"


#include <Arduino.h>
#include <SoftwareSerial.h>


void sendSMSCommand() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // THE RECIPIENT'S MOBILE NUMBER (JEN)
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"‪+6287842066617‬\""); 
  delay(100);

  // The message to be sent
  SIM900.println("ALERT: Fire or smoke detected at your premises. Please take immediate action. - Smart Alert System");
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 

}

void sendSMS(){
    // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
    // Make sure that corresponds to the baud rate of your module
    SIM900.begin(19200);

    // Give time to your GSM shield log on to network
    delay(20000);   
    
    // Send the SMS
    sendSMSCommand();
    
}