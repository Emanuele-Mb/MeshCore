#ifndef _VARIANT_H_
#define _VARIANT_H_

// ==============================================================================
//  LILYGO T-WATCH S3 (ESP32-S3) - HARDWARE PINOUT MAP
// ==============================================================================

// ------------------------------------------------------------------------------
// 1. BUS I2C (PMU AXP2101, Sensor QMC6310, RTC PCF8563)
// ------------------------------------------------------------------------------
#define I2C_SDA         10
#define I2C_SCL         11

#define PMU_IRQ         21    // Interrupt del chip di alimentazione AXP2101
#define BMA423_INT      14    // Interrupt dell'accelerometro
#define RTC_ADDR        0x51  // Indirizzo I2C dell'RTC PCF8563

// ------------------------------------------------------------------------------
// 2. RADIO LORA (Semtech SX1262)
// ------------------------------------------------------------------------------
#define LORA_MOSI       1
#define LORA_MISO       4
#define LORA_SCK        3
#define LORA_CS         5     

#define LORA_RESET      8     
#define LORA_DIO1       9     // SX1262 IRQ
#define LORA_DIO2       7     // SX1262 BUSY

// Alias 
#define SX126X_CS       LORA_CS 
#define SX126X_DIO1     LORA_DIO1
#define SX126X_BUSY     LORA_DIO2
#define SX126X_RESET    LORA_RESET

#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8

// ------------------------------------------------------------------------------
// 3. DISPLAY (ST7789 - SPI 240x240)
// ------------------------------------------------------------------------------
#define TFT_MOSI        13    
#define TFT_SCLK        18    
#define TFT_CS          12
#define TFT_DC          38    
#define TFT_RST         -1    
#define TFT_BL          45    // BackLight

#define TFT_WIDTH       240
#define TFT_HEIGHT      240

// ------------------------------------------------------------------------------
// 4. TOUCH SCREEN (Bus I2C)
// ------------------------------------------------------------------------------
#define TOUCH_SDA       39
#define TOUCH_SCL       40
#define TOUCH_INT       16
#define TOUCH_ADDR      0x38

// ------------------------------------------------------------------------------
// 5. GPS
// ------------------------------------------------------------------------------
#define GPS_RX_PIN      41
#define GPS_TX_PIN      42
#define GPS_BAUD        38400

// ------------------------------------------------------------------------------
// 6. AUDIO I2S
// ------------------------------------------------------------------------------
#define I2S_BCK         48
#define I2S_WS          15
#define I2S_DOUT        46
#define I2S_MCLK        0


#endif /* _VARIANT_H_ */