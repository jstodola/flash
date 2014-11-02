#include <Arduino.h>
#include "timer.h"

timer::timer(int value) {
    set(value);
}

void timer::set(int value) {
    _init_value = value;
    _start_time = 0;
}

void timer::start() {
    _start_time = millis();
}

int timer::remain() {
    int return_value = 0;
    unsigned int now;
    
    now = millis();
    if(_start_time + _init_value > now) {
        return_value = (_start_time + _init_value) - now;
    }
    return return_value;
}

int timer::remain_seconds() {
    return round(remain() / 1000.0);
}

uint8_t timer::is_running() {
    return remain() > 0;
}
