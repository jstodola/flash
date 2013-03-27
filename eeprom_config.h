#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

struct configuration {
    uint8_t mode;
    int backlight;
    int flash_delay;
    int start_delay;
    int calibration_duration;
    int timelapse_delay;
    uint8_t camera_bulb;
    int sensor_tolerance;
    uint8_t flash_1_enabled;
    uint8_t flash_2_enabled;
    uint8_t flash_3_enabled;
    uint8_t flash_4_enabled;
    int autofocus_time;
    int shutter_lag;
    uint8_t camera_1_enabled;
    uint8_t camera_2_enabled;
    uint8_t speaker_enabled;
};

extern struct configuration config;

void read_config();
void write_config();

#endif
