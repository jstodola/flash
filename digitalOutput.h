#ifndef DIGITALOUTPUT_H
#define DIGITALOUTPUT_H

class digitalOutput {
  public:
    digitalOutput(int pin);
    void on();
    void off();
  private:
    int pin;
};

#endif
