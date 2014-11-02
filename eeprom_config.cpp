#include <avr/eeprom.h>
#include <inttypes.h>
#include "eeprom_config.h"
#include "common.h"

uint16_t MODE_ADDR        = 1;  // 1 B
uint16_t BACKLIGHT_ADDR   = 5;  // 2 B
uint16_t FLASH_DELAY_ADDR = 10; // 2 B
uint16_t START_DELAY_ADDR = 12; // 2 B
uint16_t TIMELAPSE_INTERVAL_ADDR = 14; // 2 B
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
uint16_t SPEAKER_ENABLED_ADDR = 31; // 1 B
uint16_t DROP_1_ENABLED_ADDR  = 32; // 1 B
uint16_t DROP_2_ENABLED_ADDR  = 33; // 1 B
uint16_t DROP_3_ENABLED_ADDR  = 34; // 1 B
uint16_t DROP_4_ENABLED_ADDR  = 35; // 1 B
uint16_t DROP_1_DELAY_ADDR    = 36; // 2 B
uint16_t DROP_2_DELAY_ADDR    = 38; // 2 B
uint16_t DROP_3_DELAY_ADDR    = 40; // 2 B
uint16_t DROP_4_DELAY_ADDR    = 42; // 2 B
uint16_t DROP_1_DURATION_ADDR = 44; // 2 B
uint16_t DROP_2_DURATION_ADDR = 46; // 2 B
uint16_t DROP_3_DURATION_ADDR = 48; // 2 B
uint16_t DROP_4_DURATION_ADDR = 50; // 2 B
uint16_t DROP_1_PORT_ADDR     = 52; // 2 B
uint16_t DROP_2_PORT_ADDR     = 54; // 2 B
uint16_t DROP_3_PORT_ADDR     = 56; // 2 B
uint16_t DROP_4_PORT_ADDR     = 58; // 2 B
uint16_t SHUTTER_SPEED_SHORTEST_INDEX_ADDR = 60; // 1 B
uint16_t SHUTTER_SPEED_LONGEST_INDEX_ADDR  = 61; // 1 B
uint16_t HDR_SHOOTS_ADDR      = 62; // 2 B

struct configuration config;

void read_config() {
    config.mode = eeprom_read_byte((uint8_t *)MODE_ADDR);
    config.backlight = eeprom_read_word(&BACKLIGHT_ADDR);
    config.flash_delay = eeprom_read_word(&FLASH_DELAY_ADDR);
    config.start_delay = eeprom_read_word(&START_DELAY_ADDR);
    config.timelapse_interval = eeprom_read_word(&TIMELAPSE_INTERVAL_ADDR);
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
    config.speaker_enabled = eeprom_read_byte((uint8_t *)SPEAKER_ENABLED_ADDR);
    config.drop_1_enabled = eeprom_read_byte((uint8_t *)DROP_1_ENABLED_ADDR);
    config.drop_2_enabled = eeprom_read_byte((uint8_t *)DROP_2_ENABLED_ADDR);
    config.drop_3_enabled = eeprom_read_byte((uint8_t *)DROP_3_ENABLED_ADDR);
    config.drop_4_enabled = eeprom_read_byte((uint8_t *)DROP_4_ENABLED_ADDR);
    config.drop_1_delay = eeprom_read_word(&DROP_1_DELAY_ADDR);
    config.drop_2_delay = eeprom_read_word(&DROP_2_DELAY_ADDR);
    config.drop_3_delay = eeprom_read_word(&DROP_3_DELAY_ADDR);
    config.drop_4_delay = eeprom_read_word(&DROP_4_DELAY_ADDR);
    config.drop_1_duration = eeprom_read_word(&DROP_1_DURATION_ADDR);
    config.drop_2_duration = eeprom_read_word(&DROP_2_DURATION_ADDR);
    config.drop_3_duration = eeprom_read_word(&DROP_3_DURATION_ADDR);
    config.drop_4_duration = eeprom_read_word(&DROP_4_DURATION_ADDR);
    config.drop_1_port = eeprom_read_word(&DROP_1_PORT_ADDR);
    config.drop_2_port = eeprom_read_word(&DROP_2_PORT_ADDR);
    config.drop_3_port = eeprom_read_word(&DROP_3_PORT_ADDR);
    config.drop_4_port = eeprom_read_word(&DROP_4_PORT_ADDR);
    config.shutter_speed_shortest_index = eeprom_read_byte((uint8_t *)SHUTTER_SPEED_SHORTEST_INDEX_ADDR);
    config.shutter_speed_longest_index = eeprom_read_byte((uint8_t *)SHUTTER_SPEED_LONGEST_INDEX_ADDR);
    config.hdr_shoots = eeprom_read_word(&HDR_SHOOTS_ADDR);
}

void write_config() {
    eeprom_write_byte((uint8_t *)MODE_ADDR, config.mode);
    eeprom_write_word(&BACKLIGHT_ADDR, config.backlight);
    eeprom_write_word(&FLASH_DELAY_ADDR, config.flash_delay);
    eeprom_write_word(&START_DELAY_ADDR, config.start_delay);
    eeprom_write_word(&TIMELAPSE_INTERVAL_ADDR, config.timelapse_interval);
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
    eeprom_write_byte((uint8_t *)SPEAKER_ENABLED_ADDR, config.speaker_enabled);
    eeprom_write_byte((uint8_t *)DROP_1_ENABLED_ADDR, config.drop_1_enabled);
    eeprom_write_byte((uint8_t *)DROP_2_ENABLED_ADDR, config.drop_2_enabled);
    eeprom_write_byte((uint8_t *)DROP_3_ENABLED_ADDR, config.drop_3_enabled);
    eeprom_write_byte((uint8_t *)DROP_4_ENABLED_ADDR, config.drop_4_enabled);
    eeprom_write_word(&DROP_1_DELAY_ADDR, config.drop_1_delay);
    eeprom_write_word(&DROP_2_DELAY_ADDR, config.drop_2_delay);
    eeprom_write_word(&DROP_3_DELAY_ADDR, config.drop_3_delay);
    eeprom_write_word(&DROP_4_DELAY_ADDR, config.drop_4_delay);
    eeprom_write_word(&DROP_1_DURATION_ADDR, config.drop_1_duration);
    eeprom_write_word(&DROP_2_DURATION_ADDR, config.drop_2_duration);
    eeprom_write_word(&DROP_3_DURATION_ADDR, config.drop_3_duration);
    eeprom_write_word(&DROP_4_DURATION_ADDR, config.drop_4_duration);
    eeprom_write_word(&DROP_1_PORT_ADDR, config.drop_1_port);
    eeprom_write_word(&DROP_2_PORT_ADDR, config.drop_2_port);
    eeprom_write_word(&DROP_3_PORT_ADDR, config.drop_3_port);
    eeprom_write_word(&DROP_4_PORT_ADDR, config.drop_4_port);
    eeprom_write_byte((uint8_t *)SHUTTER_SPEED_SHORTEST_INDEX_ADDR, (uint8_t)config.shutter_speed_shortest_index);
    eeprom_write_byte((uint8_t *)SHUTTER_SPEED_LONGEST_INDEX_ADDR, (uint8_t)config.shutter_speed_longest_index);
    eeprom_write_word(&HDR_SHOOTS_ADDR, config.hdr_shoots);
}

// load default values to eeprom
void initialize_eeprom() {
    config.mode = MODE_SOUND;
    config.backlight = 128;
    config.flash_delay = 10;        // 10 ms
    config.start_delay = 0;         // start with no delay
    config.timelapse_interval = 10; // 10 s
    config.camera_bulb = 1;         // camera time is set to bulb
    config.sensor_tolerance = 5;    // tolerance 5%
    config.calibration_duration = 1000;     // 1000 ms for sensor calibration
    config.flash_1_enabled = 1;     // enable flash 1
    config.flash_2_enabled = 1;     // enable flash 2
    config.flash_3_enabled = 1;     // enable flash 3
    config.flash_4_enabled = 1;     // enable flash 4
    config.autofocus_time = 0;      // no autofocus time, manual focus is expected
    config.shutter_lag = 0;         // ??
    config.camera_1_enabled = 1;    // enable camera 1
    config.camera_2_enabled = 1;    // enable camera 2
    config.speaker_enabled = 1;     // speaker is on
    config.drop_1_enabled = 1;      // enable drop 1
    config.drop_2_enabled = 0;      // disable drop 2
    config.drop_3_enabled = 0;      // disable drop 3
    config.drop_4_enabled = 0;      // disable drop 4
    config.drop_1_delay = 0;        // 0 ms delay
    config.drop_2_delay = 0;        // 0 ms delay
    config.drop_3_delay = 0;        // 0 ms delay
    config.drop_4_delay = 0;        // 0 ms delay
    config.drop_1_duration = 20;    // 20 ms
    config.drop_2_duration = 20;    // 20 ms
    config.drop_3_duration = 20;    // 20 ms
    config.drop_4_duration = 20;    // 20 ms
    config.drop_1_port = 1;         // port 1
    config.drop_2_port = 1;         // port 1 (unless more valves are available)
    config.drop_3_port = 1;         // port 1 (unless more valves are available)
    config.drop_4_port = 1;         // port 1 (unless more valves are available) 
    config.shutter_speed_shortest_index = 0;    // cca 1 s
    config.shutter_speed_longest_index = 6;     // cca 4 s
    config.hdr_shoots = 4;          // 4 pictures for HDR

    write_config();
}
