#include "utils/delay.h"
#include "output/buzzer.h"
#include "utils/adc.h"
#include "gasSensor.h"

#include <Arduino.h>
#include <avr/io.h>

// Constants for the gas sensor
#define RL 10.0            // Load resistance in kilo ohms
#define CH4_SENSITIVITY 0.4 // Sensitivity for CH4 in ppm
#define CO_SENSITIVITY 0.4  // Sensitivity for CO in ppm
#define LPG_SENSITIVITY 0.4 // Sensitivity for LPG in ppm
#define THRESHOLD_RATIO 0.3 // For medium sensitivity to gas/smoke, high is <0.2, low is >0.4

// R0 calibration value for clean air
// This should be calibrated based on your specific sensor
float R0 = 0.85;

void initGasSensor() {
    // No need to call initADC() here if it's already called in main()
    // Just perform any gas sensor specific initialization if needed
    Serial.println("Gas sensor initialized");
}

float readGasConcentration() {
    float sensorValue = 0;
    
    // Take multiple readings for stability
    for (int i = 0; i < 100; i++) {
        sensorValue += readADC();
        _delay_us(10); // Short delay between readings for stability
    }
    sensorValue /= 100.0;
    
    // Convert to voltage (assuming 10-bit ADC with 5V reference)
    float sensorVolt = (sensorValue / 1023.0) * 5.0;
    
    // Calculate gas sensor resistance
    // RS = ((Vc * RL) / Vout) - RL
    // Simplified to: RS = (5.0 - sensorVolt) * RL / sensorVolt
    float RS_gas = (5.0 - sensorVolt) * RL / sensorVolt;
    
    // Calculate ratio (RS/R0)
    float ratio = RS_gas / R0;
    
    return ratio;
}

bool isGasDetected() {
    float ratio = readGasConcentration();
    
    // Lower ratio means higher gas concentration
    return (ratio < THRESHOLD_RATIO);
}

void processGasSensor() {
    float ratio = readGasConcentration();
    
    Serial.print("Gas Ratio (RS/R0): ");
    Serial.println(ratio);
    
    if (ratio < THRESHOLD_RATIO) {
        // Dangerous gas level detected
        Serial.println("Dangerous gas detected!");
        
        // Activate alerts - uncomment when these functions are ready
        // buzzerOn();
        // fanOn();
        // sendGSMAlert();
    } else {
        // Normal air quality
        Serial.println("Air quality normal.");
        // buzzerOff();
    }
}