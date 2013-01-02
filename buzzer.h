#ifndef BUZZER_H
#define BUZZER_H

class buzzer {
  public:
    buzzer(int pin);
    void set_value(int value);
    int get_value();
  private:
    int pin;
    int value;
};

#endif
