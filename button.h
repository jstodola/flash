#ifndef BUTTON_H
#define BUTTON_H

const uint8_t DOWN = 2;     // rotation button
const uint8_t UP   = 3;

class button {
  public:
    button(uint8_t pin,
           int debounce_delay=50,   // 50 ms
           int repeat_delay=1000,   // 1000 ms
           int repeat_rate=4);      // 4 repeats per second
    uint8_t state();
    uint8_t read();
  private:
    uint8_t pin;
    uint8_t last_state;
    uint8_t last_stable_state;
    unsigned long last_debounce_time;
    unsigned long returned_state_time;
    int debounce_delay;
    uint8_t repeating;
    int repeat_delay;
    int repeat_rate;
};

class rotaryEncoder {
  public:
    rotaryEncoder(uint8_t pin_A, uint8_t pin_B);
    ~rotaryEncoder();
    uint8_t read();
  private:
    button *A;
    button *B;
    uint8_t last_state_A;
    uint8_t last_state_B;
    uint8_t last_state;
};

#endif
