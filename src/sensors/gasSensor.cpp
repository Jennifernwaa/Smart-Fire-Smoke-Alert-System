// #include "utils/timer.h"
// #include "output/buzzer.h"
// #include "utils/adc.h"
// #include "gasSensor.h"

// #include <Arduino.h>
// #include <avr/io.h>

// // Constants for the gas sensor
// #define RL 10.0            // Load resistance in kilo ohms
// #define CH4_SENSITIVITY 0.4 // Sensitivity for CH4 in ppm
// #define CO_SENSITIVITY 0.4  // Sensitivity for CO in ppm
// #define LPG_SENSITIVITY 0.4 // Sensitivity for LPG in ppm
// #define THRESHOLD_RATIO 0.3 // For medium sensitivity to gas/smoke, high is <0.2, low is >0.4

// // Sensor failure and redundancy parameters
// #define CONSECUTIVE_READINGS_REQUIRED 3 // Number of consecutive threshold violations before alarm
// #define SENSOR_ERROR_MAX_RATIO 5.0      // Maximum acceptable ratio for valid reading
// #define SENSOR_ERROR_MIN_RATIO 0.01     // Minimum acceptable ratio for valid reading

// // State tracking variables
// uint8_t consecutiveAlerts = 0;
// uint8_t sensorErrorCount = 0;
// bool sensorFailure = false;

// // R0 calibration value for clean air
// // This should be calibrated based on your specific sensor
// float R0 = 0.85;

// void initGasSensor() {
//     // Reset state variables
//     consecutiveAlerts = 0;
//     sensorErrorCount = 0;
//     sensorFailure = false;

//     // No need to call initADC() here if it's already called in main()
//     // Just perform any gas sensor specific initialization if needed
//     Serial.println("Gas sensor initialized");
// }

// float readGasConcentration() {
//     float sensorValue = 0;
    
//     // Take multiple readings for stability
//     for (int i = 0; i < 100; i++) {
//         sensorValue += readADC();
//         delayUs(10); // Short delay between readings for stability
//     }
//     sensorValue /= 100.0;
    
//     // Convert to voltage (assuming 10-bit ADC with 5V reference)
//     float sensorVolt = (sensorValue / 1023.0) * 5.0;
    
//     // Calculate gas sensor resistance
//     // RS = ((Vc * RL) / Vout) - RL
//     // Simplified to: RS = (5.0 - sensorVolt) * RL / sensorVolt
//     float RS_gas = (5.0 - sensorVolt) * RL / sensorVolt;
    
//     // Calculate ratio (RS/R0)
//     float ratio = RS_gas / R0;

//     // Sensor error check - ratio should be within reasonable bounds
//     if (ratio > SENSOR_ERROR_MAX_RATIO || ratio < SENSOR_ERROR_MIN_RATIO) {
//         sensorErrorCount++;
        
//         // If we've seen too many errors, mark sensor as failed
//         if (sensorErrorCount > 5) {
//             sensorFailure = true;
//             Serial.println("ERROR: Gas sensor failure detected");
//         }
        
//         // Return last known good value or default to a non-alarming value
//         return 1.0;
//     } else {
//         // Reset error counter if we get a good reading
//         sensorErrorCount = 0;
//         return ratio;
//     }
//     Serial.println("Gas Ratio (RS/R0): ");
//     Serial.println(ratio);
// }

// bool isGasDetected() {

//     static unsigned long lastAlertTime = 0;
//     const unsigned long resetTimeMs = 4900; // Reset counter after 4.9 seconds of no detections

//     // If sensor is in failure mode, don't try to detect gas
//     if (sensorFailure) {
//         Serial.println("Sensor failure, cannot detect gas");
//         return false;
//     }
    
//     float ratio = readGasConcentration();
//     unsigned long currentTime = millis();
    
//     // Check if gas concentration exceeds threshold
//     if (ratio < THRESHOLD_RATIO) {
//         consecutiveAlerts++;
//         lastAlertTime = currentTime;
        
//         // Only report gas detection after multiple consecutive alerts
//         if (consecutiveAlerts >= CONSECUTIVE_READINGS_REQUIRED) {
//             return true;
//         }
//     } else {
//         // Only reset the counter if it's been a while since the last alert
//         if (currentTime - lastAlertTime > resetTimeMs) {
//             consecutiveAlerts = 0;
//         }
//     }
//     Serial.println("Gas is not detected, but it is working")
//     return false;
// }

// bool isSensorFailed() {
//     return sensorFailure;
// }

// void resetSensor() {
//     // Reset all error flags and counters
//     sensorErrorCount = 0;
//     consecutiveAlerts = 0;
//     sensorFailure = false;
//     Serial.println("Gas sensor reset");
// }


// void processGasSensor() {
//     // Check for sensor failure first
//     if (sensorFailure) {
//         Serial.println("WARNING: Gas sensor failure detected");
//         resetSensor();
//         // Could activate a different alert pattern for sensor failure
//         return;
//     }
    
//     float ratio = readGasConcentration();
    
//     Serial.print("Gas Ratio (RS/R0): ");
//     Serial.println(ratio);
    
//     // Process gas detection with redundancy check
//     if (isGasDetected()) {
//         Serial.println("ALERT: Dangerous gas level confirmed!");
//         // Activate alerts
//         buzzerOn();
//         fanOn();
//         // sendGSMAlert();
//     } else {
//         if (consecutiveAlerts > 0) {
//             Serial.print("Potential gas detected. Confirmation: ");
//             Serial.print(consecutiveAlerts);
//             Serial.print("/");
//             Serial.println(CONSECUTIVE_READINGS_REQUIRED);
//         } else {
//             Serial.println("Air quality normal.");
//             buzzerOff();
//         }
//     }

    
// }