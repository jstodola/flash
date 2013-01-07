#include <Arduino.h>
#include "digitalOutput.h"

digitalOutput::digitalOutput(uint8_t pin) {
    pinMode(pin, OUTPUT);
    this->pin = pin;
    off();
}

void digitalOutput::on() {
    digitalWrite(this->pin, HIGH);
}

void digitalOutput::off() {
    digitalWrite(this->pin, LOW);
}

