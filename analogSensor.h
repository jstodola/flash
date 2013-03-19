#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

class analogSensor {
  public:
    analogSensor(uint8_t pin);
    int get_value();
    void calibrate(unsigned long delay, int tolerance = 0);
    int get_minimal();
    int get_maximal();
  private:
    uint8_t pin;
    int min_value;
    int max_value;
};

#endif
