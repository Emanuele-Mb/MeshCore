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
        // TODO: Aggiungere lettura reale I2C dell'AXP2101
        return 4200; // Restituiamo 4.2V (batteria carica) per far avviare il sistema
    }

    const char* getManufacturerName() const override {
        return "LilyGo T-Watch S3";
    }

    void reboot() override {
        ESP.restart();
        while(1); // Blocca tutto in attesa del riavvio
    }

    uint8_t getStartupReason() const override {
        // BD_STARTUP_NORMAL è definito proprio nel file che mi hai mandato
        return BD_STARTUP_NORMAL; 
    }

    // ------------------------------------------------------------------------------
    // OVERRIDE
    // ------------------------------------------------------------------------------
    
    // Possiamo sovrascrivere powerOff() o sleep() che nel core sono "no op" (vuote)
    void sleep(uint32_t secs) override {
        digitalWrite(TFT_BL, LOW);
        esp_deep_sleep(secs * 1000000ULL);
    }
};