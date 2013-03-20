#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

class analogSensor {
  public:
    analogSensor(uint8_t pin, uint8_t capabilities = 0);
    int get_value();
    void calibrate(unsigned long delay, int tolerance = 0);
    int get_minimal();
    int get_maximal();
    uint8_t is_sound_sensor();
    uint8_t is_light_sensor();
  private:
    uint8_t pin;
    int min_value;
    int max_value;
    uint8_t capabilities;
};

#endif
