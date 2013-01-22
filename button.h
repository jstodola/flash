#ifndef BUTTON_H
#define BUTTON_H

class buttonCore {
  public:
    buttonCore();
    virtual buttonCore* get_next_button();
    virtual void set_next_button(buttonCore &next_button);
    virtual uint8_t read();
  private:
    buttonCore *_next_button;
};

class button : public buttonCore {
  public:
    button(uint8_t pin,
           uint8_t return_value=1,  // return value when pressed
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
    unsigned long last_query_time;
    unsigned long returned_state_time;
    int debounce_delay;
    uint8_t repeating;
    int repeat_delay;
    int repeat_rate;
    uint8_t return_value;
};

class rotaryEncoder : public buttonCore {
  public:
    rotaryEncoder(uint8_t pin_A,
                  uint8_t pin_B,
                  uint8_t return_value_up=1,
                  uint8_t return_value_down=1);
    ~rotaryEncoder();
    uint8_t read();
  private:
    button *A;
    button *B;
    uint8_t last_state_A;
    uint8_t last_state_B;
    uint8_t last_state;
    uint8_t return_value_up;
    uint8_t return_value_down;
};

class buttonsReader {
  public:
    buttonsReader();
    void add_button(buttonCore &new_button);
    uint8_t read();
  private:
    buttonCore *_first;
    buttonCore *_last;
};

#endif
