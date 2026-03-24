#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include "variant.h"

// --- Serial Pin Default (Hardware UART0) ---
static const uint8_t TX = 43;
static const uint8_t RX = 44;

// --- Bus I2C Default ---
static const uint8_t SDA = I2C_SDA;
static const uint8_t SCL = I2C_SCL;

// --- Bus SPI Default ---
static const uint8_t SS   = LORA_CS;
static const uint8_t MOSI = LORA_MOSI;
static const uint8_t MISO = LORA_MISO;
static const uint8_t SCK  = LORA_SCK;

// --- Pin Analogici (Standard ESP32-S3) ---
static const uint8_t A0 = 1;
static const uint8_t A1 = 2;
static const uint8_t A2 = 3;
static const uint8_t A3 = 4;
static const uint8_t A4 = 5;
static const uint8_t A5 = 6;
static const uint8_t A6 = 7;
static const uint8_t A7 = 8;
static const uint8_t A8 = 9;
static const uint8_t A9 = 10;
static const uint8_t A10 = 11;
static const uint8_t A11 = 12;
static const uint8_t A12 = 13;
static const uint8_t A13 = 14;
static const uint8_t A14 = 15;
static const uint8_t A15 = 16;
static const uint8_t A16 = 17;
static const uint8_t A17 = 18;
static const uint8_t A18 = 19;
static const uint8_t A19 = 20;

// --- Pin Touch Capacitivi (Standard ESP32-S3) ---
static const uint8_t T1 = 1;
static const uint8_t T2 = 2;
static const uint8_t T3 = 3;
static const uint8_t T4 = 4;
static const uint8_t T5 = 5;
static const uint8_t T6 = 6;
static const uint8_t T7 = 7;
static const uint8_t T8 = 8;
static const uint8_t T9 = 9;
static const uint8_t T10 = 10;
static const uint8_t T11 = 11;
static const uint8_t T12 = 12;
static const uint8_t T13 = 13;
static const uint8_t T14 = 14;

#endif /* Pins_Arduino_h */