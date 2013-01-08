#include <Arduino.h>
#include <LiquidCrystal.h>
#include "display.h"

display::display(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) :
         LiquidCrystal(rs, enable, d0, d1, d2, d3){
}

void display::begin(uint8_t cols, uint8_t lines) {
  LiquidCrystal::begin(cols, lines);
  num_columns = cols;
  num_rows = lines;
}

void display::begin_backlight(uint8_t backlight_pin, uint8_t value) {
  this->backlight_pin = backlight_pin;
  pinMode(backlight_pin, OUTPUT);
  set_backlight(value);
}

void display::set_backlight(uint8_t value) {
  analogWrite(backlight_pin, value);
}

uint8_t display::get_columns() {
    return num_columns;
}

uint8_t display::get_rows() {
    return num_rows;
}

