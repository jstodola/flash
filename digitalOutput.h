#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

class digitalOutput {
  public:
    digitalOutput(uint8_t pin);
    void on();
    void off();
  private:
    uint8_t pin;
};

#endif
