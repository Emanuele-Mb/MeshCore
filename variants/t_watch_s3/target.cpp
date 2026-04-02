#include <Arduino.h>
#include "target.h"
#include <SPI.h>
#include <helpers/ESP32Board.h>

TWatchS3Board board;

static SPIClass spi_lora(FSPI); 

CustomSX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RESET, LORA_DIO2, spi_lora);

CustomSX1262Wrapper radio_driver(radio, board);

ESP32RTCClock fallback_clock;
AutoDiscoverRTCClock rtc_clock(fallback_clock);

EnvironmentSensorManager sensors;

bool radio_init() {
  board.begin();
  
  fallback_clock.begin();
  rtc_clock.begin(Wire);

  spi_lora.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  
  return radio.std_init(&spi_lora);
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