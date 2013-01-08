#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>

class display : public LiquidCrystal {
  public:
    display(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
    void begin(uint8_t cols, uint8_t lines);
    void begin_backlight(uint8_t backlight_pin, uint8_t value);
    void set_backlight(uint8_t value);
    uint8_t get_columns();
    uint8_t get_rows();
  private:
    uint8_t backlight_pin;
    uint8_t num_columns;
    uint8_t num_rows;
};

#endif
