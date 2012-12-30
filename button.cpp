#include <Arduino.h>
#include "button.h"

button::button(int pin) {
    pinMode(pin, INPUT);
    this->last_state = digitalRead(pin);
    this->pin = pin;
    this->last_debounce_time = millis();
}

int button::get_state() {

    int button_state;
    int reading;

    reading = digitalRead(this->pin);
    if(reading != this->last_state) {
        this->last_debounce_time = millis();
    }

    if((int)(millis() - this->last_debounce_time) > debounce_delay) {
        button_state = reading;
    }else {
        button_state = this->last_state;
    }

    this->last_state = reading;
    return(button_state);
}

