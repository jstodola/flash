#include <Arduino.h>
#include "flash.h"

flash::flash(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(this->pin, LOW);
    this->pin = pin;
}

void flash::fire_start() {
    digitalWrite(this->pin, HIGH);
}

void flash::fire_finish() {
    digitalWrite(this->pin, LOW);
}

void flash::fire() {
    fire_start();
    delay(50);
    fire_finish();
}
