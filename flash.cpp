#include <Arduino.h>
#include "flash.h"

flash::flash(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(this->pin, LOW);
    this->pin = pin;
}

void flash::fire() {
    digitalWrite(this->pin, HIGH);
    delay(50);
    digitalWrite(this->pin, LOW);
}
