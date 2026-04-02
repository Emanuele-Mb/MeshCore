#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <XPowersLib.h>
#include "variant.h"

extern XPowersAXP2101 PMU;    

class TWatchS3Board : public mesh::MainBoard {
public:
    TWatchS3Board() {}

    void begin() {
        Serial.println("======================");
        Serial.println("LilyGo T-Watch S3 init");
        Serial.println("======================");

        // 1. PMU and I2C init
        Wire.begin(I2C_SDA, I2C_SCL);

        // 2. AXP2101 Init (Power Management Unit)
        if (PMU.begin(Wire, AXP2101_SLAVE_ADDRESS, I2C_SDA, I2C_SCL)) {
            Serial.println("PMU AXP2101 rilevato con successo!");
            
            // LoRa chip powering (ALDO4)
            PMU.setALDO4Voltage(3300); // 3.3 Volt
            PMU.enableALDO4();         
            
            // Touch and Screen powering (BLDO1 e ALDO2)
            PMU.setBLDO1Voltage(3300);
            PMU.enableBLDO1();
            PMU.setALDO2Voltage(3300);
            PMU.enableALDO2();
            

        } else {
            Serial.println("--- CRITICAL ERROR: PMU NOT FOUND ---");
        }

        // 3. Backlight high
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH); 

        pinMode(LORA_CS, OUTPUT);
        digitalWrite(LORA_CS, HIGH);

        Serial.println("Hardware init done");
    
    }

    // ------------------------------------------------------------------------------
    // MESH::MAINBOARD
    // ------------------------------------------------------------------------------

    uint16_t getBattMilliVolts() override {
        if (PMU.isBatteryConnect()) {
            return PMU.getBattVoltage(); 
        }
        return 0; // Return 0 if watch has no battery
    }

    const char* getManufacturerName() const override {
        return "LilyGo T-Watch S3";
    }

    void reboot() override {
        Serial.println("Rebooting...");
        ESP.restart();
        while(1); // Wait for hardware reboot
    }

    uint8_t getStartupReason() const override {
        return BD_STARTUP_NORMAL; 
    }

    // ------------------------------------------------------------------------------
    // Energy Save
    // ------------------------------------------------------------------------------
    
    void sleep(uint32_t secs) override {
        Serial.printf("Deep Sleep for %d seconds...\n", secs);
        digitalWrite(TFT_BL, LOW);
        
        esp_deep_sleep(secs * 1000000ULL);
    }

    void powerOff() {
        Serial.println("Turning off the watch...");
        digitalWrite(TFT_BL, LOW);
        
        PMU.shutdown(); 
        
        esp_deep_sleep_start();
    }
};