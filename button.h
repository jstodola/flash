#ifndef BUTTON_H
#define BUTTON_H

const int debounce_delay = 50;   // 50 ms

class button {
  public:
    button(int pin);
    int get_state();
  private:
    int pin;
    int last_state;
    unsigned long last_debounce_time;
};

#endif
