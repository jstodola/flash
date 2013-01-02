#ifndef FLASH_H
#define FLASH_H

class flash {
  public:
    flash(int pin);
    void fire();
  private:
    int pin;
};

#endif
