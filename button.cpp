#include <Arduino.h>
#include "button.h"

button::button(int pin) {
    // default debounce time is 50 ms,
    // wait 1000 ms before repeating, repeat 4 times per second
    init(pin, debounce_delay_def, repeat_delay_def, repeat_rete_def);
}

button::button(int pin, int debounce_delay, int repeat_delay, int repeat_rate) {
    init(pin, debounce_delay, repeat_delay, repeat_rate);
}

void button::init(int pin, int debounce_delay, int repeat_delay, int repeat_rate) {
    
    int button_state;
    unsigned long now;
    
    pinMode(pin, INPUT);

    button_state = digitalRead(pin);
    now = millis();

    this->last_state = button_state;
    this->last_stable_state = button_state;
    this->pin = pin;
    this->last_debounce_time = now;
    this->returned_state_time = now;
    this->debounce_delay = debounce_delay;
    this->repeat_delay = repeat_delay;
    this->repeat_rate = repeat_rate;
    this->repeating = 0;
}

// returns state of button after debouncing
int button::state() {

    int button_state;
    int reading;

    reading = digitalRead(this->pin);
    if(reading != this->last_state) {
        this->last_debounce_time = millis();
    }

    if((int)(millis() - this->last_debounce_time) > this->debounce_delay) {
        button_state = reading;
    }else {
        button_state = this->last_state;
    }

    this->last_state = reading;
    return(button_state);
}

// returns one HIGH value for each key press, also send HIGH for repeating
// events when key is pressed for a long time
int button::read() {
    
    int current_state;
    int return_state = LOW;
    int event_delay;
    unsigned long now;

    now = millis();
    current_state = state();

    if(current_state != this->last_stable_state) {
        this->repeating = 0;
        this->returned_state_time = now;
        return_state = current_state;
    } else {
        if(this->repeating) {
            event_delay = 1000 / this->repeat_rate;
        } else {
            event_delay = this->repeat_delay;
        }
        
        // it is time to return another button event
        if(this->returned_state_time + event_delay < now) {
            this->repeating = 1;
            this->returned_state_time = now;
            return_state = current_state;
        }

    }

    this->last_stable_state = current_state;
    return return_state;
}
