#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

struct configuration {
    uint8_t mode;
    int backlight;
    int flash_delay;
    int start_delay;
    int calibration_duration;
    int timelapse_interval;
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
    uint8_t drop_1_enabled;
    uint8_t drop_2_enabled;
    uint8_t drop_3_enabled;
    uint8_t drop_4_enabled;
    int drop_1_delay;
    int drop_2_delay;
    int drop_3_delay;
    int drop_4_delay;
    int drop_1_duration;
    int drop_2_duration;
    int drop_3_duration;
    int drop_4_duration;
    int drop_1_port;
    int drop_2_port;
    int drop_3_port;
    int drop_4_port;
    int8_t shutter_speed_shortest_index;
    int8_t shutter_speed_longest_index;
    int hdr_shoots;
};

extern struct configuration config;

void read_config();
void write_config();
void initialize_eeprom();

#endif
