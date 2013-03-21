#include <Arduino.h>
#include "camera.h"

camera::camera(uint8_t focus_pin, uint8_t shutter_pin) {

    pinMode(focus_pin, OUTPUT);
    pinMode(shutter_pin, OUTPUT);

    this->focus_pin = focus_pin;
    this->shutter_pin = shutter_pin;
    stop();
}

void camera::focus_start() {
    digitalWrite(this->focus_pin, HIGH);
}

void camera::focus_stop() {
    digitalWrite(this->focus_pin, LOW);
}

void camera::shutter_start() {
    digitalWrite(this->shutter_pin, HIGH);
}

void camera::shutter_stop() {
    digitalWrite(this->shutter_pin, LOW);
}

void camera::start(int autofocus_time) {
    focus_start();
    if(autofocus_time > 0) {
        delay(autofocus_time);
    }
    shutter_start();
}

void camera::stop() {
    shutter_stop();
    focus_stop();
}

