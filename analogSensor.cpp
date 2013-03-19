#include <Arduino.h>
#include "analogSensor.h"

analogSensor::analogSensor(uint8_t pin) {
    pinMode(pin, INPUT);
    this->pin = pin;
    this->min_value = 0;
    this->max_value = 1023;
}

int analogSensor::get_value() {
    return analogRead(this->pin);
}

void analogSensor::calibrate(unsigned long delay, int tolerance) {
    
    unsigned long start;
    int value;
    
    this->min_value = 1023;
    this->max_value = 0;

    start = millis();
    do {
        value = get_value();
        if(value > this->max_value) {
            this->max_value = value;
        }
        if(value < this->min_value) {
            this->min_value = value;
        }
    } while(start + delay > millis());
    
    if(tolerance > 0) {
        min_value -= (min_value * tolerance) / 100;
        if(min_value < 0) {
            min_value = 0;
        }
        max_value += (max_value * tolerance) / 100;
        if(max_value > 1023) {
            max_value = 1023;
        }
    }
}

int analogSensor::get_minimal() {
    return this->min_value;
}

int analogSensor::get_maximal() {
    return this->max_value;
}
