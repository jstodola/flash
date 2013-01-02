#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

class analogSensor {
  public:
    analogSensor(int pin);
    int get_value();
    void calibrate(unsigned long delay);
    int get_minimal();
    int get_maximal();
  private:
    int pin;
    int min_value;
    int max_value;
};

#endif
