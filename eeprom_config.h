#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

struct configuration {
    uint8_t mode;
    int backlight;
    int flash_delay;
    int start_delay;
};

extern struct configuration config;

void read_config();
void write_config();

#endif
