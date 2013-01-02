#include <Arduino.h>
#include "digitalOutput.h"

digitalOutput::digitalOutput(int pin) {
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

