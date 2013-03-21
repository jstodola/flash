#include <avr/eeprom.h>
#include <inttypes.h>
#include "eeprom_config.h"

uint16_t MODE_ADDR        = 1;  // 1 B
uint16_t BACKLIGHT_ADDR   = 5;  // 2 B
uint16_t FLASH_DELAY_ADDR = 10; // 2 B
uint16_t START_DELAY_ADDR = 12; // 2 B
uint16_t TIMELAPSE_DELAY_ADDR = 14; // 2 B
uint16_t CAMERA_BULB_ADDR = 16;  // 1 B
uint16_t SENSOR_TOLERANCE_ADDR = 17;  // 2 B
uint16_t CALIBRATION_DURATION_ADDR = 19;  // 2 B
uint16_t FLASH_1_ENABLED_ADDR = 21; // 1 B
uint16_t FLASH_2_ENABLED_ADDR = 22; // 1 B
uint16_t FLASH_3_ENABLED_ADDR = 23; // 1 B
uint16_t FLASH_4_ENABLED_ADDR = 24; // 1 B
uint16_t AUTOFOCUS_TIME_ADDR  = 25; // 2 B
uint16_t SHUTTER_LAG_ADDR     = 27; // 2 B
uint16_t CAMERA_1_ENABLED_ADDR = 29; // 1 B
uint16_t CAMERA_2_ENABLED_ADDR = 30; // 1 B

struct configuration config;

void read_config() {
    config.mode = eeprom_read_byte((uint8_t *)MODE_ADDR);
    config.backlight = eeprom_read_word(&BACKLIGHT_ADDR);
    config.flash_delay = eeprom_read_word(&FLASH_DELAY_ADDR);
    config.start_delay = eeprom_read_word(&START_DELAY_ADDR);
    config.timelapse_delay = eeprom_read_word(&TIMELAPSE_DELAY_ADDR);
    config.camera_bulb = eeprom_read_byte((uint8_t *)CAMERA_BULB_ADDR);
    config.sensor_tolerance = eeprom_read_word(&SENSOR_TOLERANCE_ADDR);
    config.calibration_duration = eeprom_read_word(&CALIBRATION_DURATION_ADDR);
    config.flash_1_enabled = eeprom_read_byte((uint8_t *)FLASH_1_ENABLED_ADDR);
    config.flash_2_enabled = eeprom_read_byte((uint8_t *)FLASH_2_ENABLED_ADDR);
    config.flash_3_enabled = eeprom_read_byte((uint8_t *)FLASH_3_ENABLED_ADDR);
    config.flash_4_enabled = eeprom_read_byte((uint8_t *)FLASH_4_ENABLED_ADDR);
    config.autofocus_time = eeprom_read_word(&AUTOFOCUS_TIME_ADDR);
    config.shutter_lag = eeprom_read_word(&SHUTTER_LAG_ADDR);
    config.camera_1_enabled = eeprom_read_byte((uint8_t *)CAMERA_1_ENABLED_ADDR);
    config.camera_2_enabled = eeprom_read_byte((uint8_t *)CAMERA_2_ENABLED_ADDR);
}

void write_config() {
    eeprom_write_byte((uint8_t *)MODE_ADDR, config.mode);
    eeprom_write_word(&BACKLIGHT_ADDR, config.backlight);
    eeprom_write_word(&FLASH_DELAY_ADDR, config.flash_delay);
    eeprom_write_word(&START_DELAY_ADDR, config.start_delay);
    eeprom_write_word(&TIMELAPSE_DELAY_ADDR, config.timelapse_delay);
    eeprom_write_byte((uint8_t *)CAMERA_BULB_ADDR, config.camera_bulb);
    eeprom_write_word(&SENSOR_TOLERANCE_ADDR, config.sensor_tolerance);
    eeprom_write_word(&CALIBRATION_DURATION_ADDR, config.calibration_duration);
    eeprom_write_byte((uint8_t *)FLASH_1_ENABLED_ADDR, config.flash_1_enabled);
    eeprom_write_byte((uint8_t *)FLASH_2_ENABLED_ADDR, config.flash_2_enabled);
    eeprom_write_byte((uint8_t *)FLASH_3_ENABLED_ADDR, config.flash_3_enabled);
    eeprom_write_byte((uint8_t *)FLASH_4_ENABLED_ADDR, config.flash_4_enabled);
    eeprom_write_word(&AUTOFOCUS_TIME_ADDR, config.autofocus_time);
    eeprom_write_word(&SHUTTER_LAG_ADDR, config.shutter_lag);
    eeprom_write_byte((uint8_t *)CAMERA_1_ENABLED_ADDR, config.camera_1_enabled);
    eeprom_write_byte((uint8_t *)CAMERA_2_ENABLED_ADDR, config.camera_2_enabled);
}

