#ifndef FLASH_H
#define FLASH_H

class flash {
  public:
    flash(int pin);
    void fire_start();
    void fire_finish();
    void fire();
  private:
    int pin;
};

#endif
