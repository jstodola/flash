#ifndef BUTTON_H
#define BUTTON_H

const int DOWN = 2;     // rotation button
const int UP   = 3;

class button {
  public:
    button(int pin,
           int debounce_delay=50,   // 50 ms
           int repeat_delay=1000,   // 1000 ms
           int repeat_rate=4);      // 4 repeats per second
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
};

class rotaryEncoder {
  public:
    rotaryEncoder(int pin_A, int pin_B);
    ~rotaryEncoder();
    int read();
  private:
    button *A;
    button *B;
    int last_state_A;
    int last_state_B;
    int last_state;
};

#endif
