// gsm.cpp
#include "gsm.h"
#include <Arduino.h>
#include "utils/timer.h"

// Define GSM module pins
#define GSM_RX_PIN 8  // Connect to SIM900 TXD
#define GSM_TX_PIN 7  // Connect to SIM900 RXD

// Emergency contact number (replace with actual number)
#define EMERGENCY_CONTACT "+6285763252592"

// Flag to track GSM module status
static bool gsmInitialized = false;

/**
 * Initialize GSM module
 */
void initGSM() {
  // Initialize hardware serial communication with SIM900
  // Using Serial instead of SoftwareSerial to avoid interrupt conflicts
  Serial.begin(19200);
  
  Serial.println("Initializing GSM module...");
  
  // Give time for the GSM module to boot and connect to network
  delay(10000);  // 10 seconds initial delay
  
  // Basic AT command to check if module is responding
  Serial.println("AT");
  delay(1000);
  
  // Set SMS text mode
  Serial.println("AT+CMGF=1");
  delay(1000);
  
  // Set GSM module to full functionality
  Serial.println("AT+CFUN=1");
  delay(2000);
  
  // Check signal quality
  Serial.println("AT+CSQ");
  delay(1000);
  
  // Check network registration status
  Serial.println("AT+CREG?");
  delay(1000);
  
  // Set character set to GSM
  Serial.println("AT+CSCS=\"GSM\"");
  delay(1000);
  
  Serial.println("GSM module initialized");
  gsmInitialized = true;
  
  // Empty the serial buffer
  while (Serial.available()) {
    Serial.read();
  }
}

/**
 * Check if GSM module is ready
 * @return true if module is ready, false otherwise
 */
bool isGSMReady() {
  if (!gsmInitialized) {
    return false;
  }
  
  // Send AT command to check if module is responsive
  Serial.println("AT");
  delay(500);
  
  // Wait for response
  unsigned long startTime = millis();
  while (millis() - startTime < 2000) {
    if (Serial.available()) {
      String response = Serial.readString();
      if (response.indexOf("OK") != -1) {
        return true;
      }
    }
  }
  
  return false;
}

/**
 * Send SMS alert to the emergency contact
 * @param message The alert message to send
 */
void sendSMSAlert(const char* message) {
  sendSMS(EMERGENCY_CONTACT, message);
}

/**
 * Send SMS to a specific phone number
 * @param phoneNumber The recipient's phone number
 * @param message The message to send
 */
void sendSMS(const char* phoneNumber, const char* message) {
  if (!gsmInitialized) {
    Serial.println("GSM module not initialized!");
    return;
  }
  
  // Clear any pending data
  while (Serial.available()) {
    Serial.read();
  }
  
  Serial.print("Sending SMS to: ");
  Serial.println(phoneNumber);
  
  // Set SMS mode
  Serial.println("AT+CMGF=1");
  delay(500);
  
  // Set recipient phone number
  Serial.print("AT+CMGS=\"");
  Serial.print(phoneNumber);
  Serial.println("\"");
  delay(500);
  
  // Compose message
  Serial.print(message);
  delay(500);
  
  // End message with Ctrl+Z character (ASCII 26)
  Serial.write(26);
  delay(5000); // Give module time to send SMS
  
  Serial.println("SMS sent");
}

/**
 * Make a call to a specific number for urgent alerts
 * @param phoneNumber The phone number to call
 */
void makeCall(const char* phoneNumber) {
  if (!gsmInitialized) {
    Serial.println("GSM module not initialized!");
    return;
  }
  
  Serial.print("Calling: ");
  Serial.println(phoneNumber);
  
  // Dial the number
  Serial.print("ATD");
  Serial.print(phoneNumber);
  Serial.println(";");
  
  // Let it ring for 20 seconds
  delay(20000);
  
  // Hang up
  Serial.println("ATH");
  delay(1000);
  
  Serial.println("Call ended");
}

/**
 * Process any incoming SMS messages
 * Can be extended to handle remote commands via SMS
 */
void processGSMMessages() {
  if (!gsmInitialized) {
    return;
  }
  
  // Check for new messages
  Serial.println("AT+CMGL=\"ALL\"");
  delay(1000);
  
  // Read and process response (basic implementation)
  if (Serial.available()) {
    String response = Serial.readString();
    
    // You can add logic here to process specific commands from SMS
    // Example: if(response.indexOf("RESET") != -1) { ... }
    
    // For now, just print out any received message
    if (response.indexOf("+CMGL:") != -1) {
      Serial.println("New message received:");
      Serial.println(response);
    }
  }
}