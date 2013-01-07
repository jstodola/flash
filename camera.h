#ifndef CAMERA_H
#define CAMERA_H

class camera {
  public:
    camera(uint8_t focus_pin, uint8_t shutter_pin);
    void focus_start();
    void focus_stop();
    void shutter_start();
    void shutter_stop();
    void start();
    void stop();
  private:
    uint8_t focus_pin;
    uint8_t shutter_pin;
};

#endif
