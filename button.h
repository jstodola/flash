#ifndef BUTTON_H
#define BUTTON_H

const int debounce_delay_def = 50;   // 50 ms
const int repeat_delay_def = 1000;   // 1000 ms
const int repeat_rate_def = 4;       // 4 repeats per second

class button {
  public:
    button(int pin);
    button(int pin, int debounce_delay, int repeat_delay, int repeat_rate);
    int state();
    int read();
  private:
    int pin;
    int last_state;
    int last_stable_state;
    unsigned long last_debounce_time;
    unsigned long returned_state_time;
    int debounce_delay;
    int repeating;
    int repeat_delay;
    int repeat_rate;
    void init(int pin, int debounce_delay, int repeat_delay, int repeat_rate);
};

#endif
