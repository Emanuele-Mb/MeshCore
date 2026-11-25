#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <XPowersLib.h>
#include <helpers/ESP32Board.h>
#include "variant.h"

extern XPowersAXP2101 PMU;

class TWatchS3Board : public ESP32Board {
public:
    TWatchS3Board() {}

    void begin() {
        ESP32Board::begin();

        Serial.println("======================");
        Serial.println("LilyGo T-Watch S3 init");
        Serial.println("======================");

        // 1. PMU and I2C init
        Wire.begin(I2C_SDA, I2C_SCL);

        // 2. AXP2101 Init (Power Management Unit)
        if (PMU.begin(Wire, AXP2101_SLAVE_ADDRESS, I2C_SDA, I2C_SCL)) {
            Serial.println("PMU AXP2101 rilevato con successo!");

            PMU.setALDO4Voltage(3300);
            PMU.enableALDO4();

            PMU.disableALDO2(); // Backlight
            PMU.disableALDO3(); // Display ST7789 + Touch
            PMU.disableBLDO1();
            PMU.disableBLDO2(); // Vibration DRV2605

            delay(50);
        } else {
            Serial.println("--- CRITICAL ERROR: PMU NOT FOUND ---");
        }

        // 3. Backlight LOW & LoRa CS HIGH
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, LOW);

        pinMode(LORA_CS, OUTPUT);
        digitalWrite(LORA_CS, HIGH);

        Serial.println("Hardware init done");
    }

    uint16_t getBattMilliVolts() override {
        if (PMU.isBatteryConnect()) {
            return PMU.getBattVoltage();
        }
        return 0;
    }

    const char* getManufacturerName() const override {
        return "LilyGo T-Watch S3";
    }

    void reboot() override {
        Serial.println("Rebooting...");
        ESP.restart();
        while (1);
    }

    void powerOff() {
        Serial.println("Turning off the watch...");
        digitalWrite(TFT_BL, LOW);
        PMU.shutdown();
        esp_deep_sleep_start();
    }
};
