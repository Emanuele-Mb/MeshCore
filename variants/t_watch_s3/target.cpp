#include <Arduino.h>
#include "target.h"
#include <SPI.h>
#include <helpers/ESP32Board.h>
#include <XPowersLib.h>

XPowersAXP2101 PMU;

TWatchS3Board board;

static SPIClass spi_lora(HSPI); 

CustomSX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RESET, LORA_DIO2, spi_lora);

CustomSX1262Wrapper radio_driver(radio, board);

ESP32RTCClock fallback_clock;
AutoDiscoverRTCClock rtc_clock(fallback_clock);

EnvironmentSensorManager sensors;

bool radio_init() {
  //Serial.println("[1] Board.begin()...");
  board.begin();
  
  //Serial.println("[2] Fallback_clock...");
  fallback_clock.begin();
  
  //Serial.println("[3] Rtc_clock...");
  rtc_clock.begin(Wire);

  //Serial.println("[4] Spi_lora.begin...");
  spi_lora.begin(LORA_SCK, LORA_MISO, LORA_MOSI, -1);
  
  //Serial.println("[5] Radio.std_init (RadioLib)...");
  bool result = radio.std_init(&spi_lora);
  
  //Serial.println("[6] Success!");
  return result;
}

uint32_t radio_get_rng_seed() {
  return radio.random(0x7FFFFFFF);
}

void radio_set_params(float freq, float bw, uint8_t sf, uint8_t cr) {
  radio.setFrequency(freq);
  radio.setSpreadingFactor(sf);
  radio.setBandwidth(bw);
  radio.setCodingRate(cr);
}

void radio_set_tx_power(int8_t dbm) {
  radio.setOutputPower(dbm);
}

mesh::LocalIdentity radio_new_identity() {
  RadioNoiseListener rng(radio);
  return mesh::LocalIdentity(&rng); 
}