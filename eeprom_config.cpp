#include <avr/eeprom.h>
#include <inttypes.h>
#include "eeprom_config.h"

uint16_t MODE_ADDR        = 1;  // 1 B
uint16_t BACKLIGHT_ADDR   = 5;  // 1 B
uint16_t FLASH_DELAY_ADDR = 10; // 2 B
uint16_t START_DELAY_ADDR = 12; // 2 B
uint16_t TIMELAPSE_DELAY_ADDR = 14; // 2 B
uint16_t CAMERA_BULB_ADDR = 16;  // 1 B

struct configuration config;

void read_config() {
    config.mode = eeprom_read_byte((uint8_t *)MODE_ADDR);
    config.backlight = eeprom_read_word(&BACKLIGHT_ADDR);
    config.flash_delay = eeprom_read_word(&FLASH_DELAY_ADDR);
    config.start_delay = eeprom_read_word(&START_DELAY_ADDR);
    config.timelapse_delay = eeprom_read_word(&TIMELAPSE_DELAY_ADDR);
    config.camera_bulb = eeprom_read_byte((uint8_t *)CAMERA_BULB_ADDR);
}

void write_config() {
    eeprom_write_byte((uint8_t *)MODE_ADDR, config.mode);
    eeprom_write_word(&BACKLIGHT_ADDR, config.backlight);
    eeprom_write_word(&FLASH_DELAY_ADDR, config.flash_delay);
    eeprom_write_word(&START_DELAY_ADDR, config.start_delay);
    eeprom_write_word(&TIMELAPSE_DELAY_ADDR, config.timelapse_delay);
    eeprom_write_byte((uint8_t *)CAMERA_BULB_ADDR, config.camera_bulb);
}

