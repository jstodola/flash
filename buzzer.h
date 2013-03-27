#ifndef BUZZER_H
#define BUZZER_H

class buzzer {
  public:
    buzzer(uint8_t pin);
    void set_value(uint8_t value);
    uint8_t get_value();
    void beep(int length = 5);
  private:
    uint8_t pin;
    uint8_t value;
};

#endif
