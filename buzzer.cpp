#include <Arduino.h>
#include "buzzer.h"

buzzer::buzzer(int pin) {
    pinMode(pin, OUTPUT);
    this->pin = pin;
    set_value(0);
}

void buzzer::set_value(int value) {
    analogWrite(this->pin, value);
    this->value = value;
}

int buzzer::get_value() {
    return this->value;
}
