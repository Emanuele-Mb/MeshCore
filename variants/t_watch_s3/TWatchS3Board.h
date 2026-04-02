#pragma once

#include <Arduino.h>

class TWatchS3Board : public mesh::MainBoard {
public:
    TWatchS3Board() {}

    void begin() {
        pinMode(LORA_CS, OUTPUT);
        digitalWrite(LORA_CS, HIGH);
        
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, LOW); 
    }

    // ------------------------------------------------------------------------------
    // MESH:MAINBOARD functions
    // ------------------------------------------------------------------------------

    uint16_t getBattMilliVolts() override {
        // TODO: Read real battery level from I2C of the AXP2101 chip
        return 4200;
    }

    const char* getManufacturerName() const override {
        return "LilyGo T-Watch S3";
    }

    void reboot() override {
        ESP.restart();
        while(1); // Blocca tutto in attesa del riavvio
    }

    uint8_t getStartupReason() const override {
        return BD_STARTUP_NORMAL; 
    }

    // ------------------------------------------------------------------------------
    // OVERRIDE
    // ------------------------------------------------------------------------------
    
    void sleep(uint32_t secs) override {
        digitalWrite(TFT_BL, LOW);
        esp_deep_sleep(secs * 1000000ULL);
    }

    //TODO: power off function override
};