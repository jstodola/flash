#ifndef TIMER_H
#define TIMER_H

class timer {
  public:
    timer(int value = 0);
    void set(int value);
    void start();
    int remain();
    int remain_seconds();
    uint8_t is_running();
  private:
    int _init_value;
    unsigned long _start_time;
};

#endif
