#ifndef CAMERA_H
#define CAMERA_H

class camera {
  public:
    camera(int focus_pin, int shutter_pin);
    void focus_start();
    void focus_stop();
    void shutter_start();
    void shutter_stop();
    void start();
    void stop();
  private:
    int focus_pin;
    int shutter_pin;
};

#endif
