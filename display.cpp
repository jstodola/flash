#include <Arduino.h>
#include <LiquidCrystal.h>
#include "display.h"

display::display(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) :
         LiquidCrystal(rs, enable, d0, d1, d2, d3){
}

void display::begin(uint8_t cols, uint8_t lines) {
    LiquidCrystal::begin(cols, lines);
    _num_columns = cols;
    _num_rows = lines;
}

void display::begin_backlight(uint8_t backlight_pin, uint8_t backlight_level) {
    _backlight_pin = backlight_pin;
    pinMode(_backlight_pin, OUTPUT);
    set_backlight(backlight_level);
}

void display::set_backlight(uint8_t backlight_level) {
    _backlight_level = backlight_level;
    analogWrite(_backlight_pin, _backlight_level);
}

uint8_t display::get_backlight() {
    return _backlight_level;
}

uint8_t display::get_columns() {
    return _num_columns;
}

uint8_t display::get_rows() {
    return _num_rows;
}

void display::set_backlight_on() {
    analogWrite(_backlight_pin, _backlight_level);
}

void display::set_backlight_off() {
    analogWrite(_backlight_pin, 0);
}
