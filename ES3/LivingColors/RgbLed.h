#ifndef RGBLED_H
#define RGBLED_H

#include "IRgb.h"

class RgbLed: public IRgb {
  private:
    int pinr;
    int ping;
    int pinb;
  public:
    RgbLed(int pinr, int ping, int pinb);
    void SetColor(int hue);
};

#endif
