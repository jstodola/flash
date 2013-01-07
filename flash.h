#ifndef FLASH_H
#define FLASH_H

class flash {
  public:
    flash(uint8_t pin);
    void fire_start();
    void fire_finish();
    void fire();
  private:
    uint8_t pin;
};

#endif
