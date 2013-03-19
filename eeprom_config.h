#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

struct configuration {
    uint8_t mode;
    int backlight;
    int flash_delay;
    int start_delay;
    int timelapse_delay;
    uint8_t camera_bulb;
    int sensor_tolerance;
};

extern struct configuration config;

void read_config();
void write_config();

#endif
