#include <Arduino.h>
#include "buzzer.h"

buzzer::buzzer(uint8_t pin) {
    pinMode(pin, OUTPUT);
    this->pin = pin;
    set_value(0);
}

void buzzer::set_value(uint8_t value) {
    analogWrite(this->pin, value);
    this->value = value;
}

uint8_t buzzer::get_value() {
    return this->value;
}
