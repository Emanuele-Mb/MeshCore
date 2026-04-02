/*#include <Arduino.h>
#include <Wire.h>
#include "variant.h"
#include <RadioLib.h>
#include <XPowersLib.h>
#include "target.h"

const uint8_t PMU_ADDR = 0x34;
//CustomSX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RESET, LORA_DIO2);

void init(){

    radio_init();
    Serial.begin(115200);
    delay(2000);
    Wire.beginTransmission(PMU_ADDR);
    if (Wire.endTransmission() != 0) {
        Serial.println("--- AXP2101 PMU not found! ---");
        while (1); 
    }
    Serial.println("PMU detected");

    Wire.begin(I2C_SDA, I2C_SCL);

    Wire.beginTransmission(0x34);
    Wire.write(0x95); // aldo4 voltage register
    Wire.write(0x1C); // 3.3v hex code
    Wire.endTransmission();
    
    // current power state
    Wire.beginTransmission(0x34);
    Wire.write(0x90); // power state register
    Wire.endTransmission();
    Wire.requestFrom(0x34, 1); // read current power state
    uint8_t state = Wire.read();

    // turn on aldo4
    Wire.beginTransmission(0x34);
    Wire.write(0x90);
    Wire.write(state | 0x08); 
    Wire.endTransmission();

    delay(100);

    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
}*/
/*
void loop(){
    int state =radio.transmit("Hello world");
    if (state == RADIOLIB_ERR_NONE) {
        Serial.println("Transmission successful!");
    } else {
        Serial.print("Transmission failed");
    }
    delay(5000);
}*/





