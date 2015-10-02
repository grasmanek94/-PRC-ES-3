#ifndef INFRAREDSENSOR_H
#define INFRAREDSENSOR_H
#include <Arduino.h>

class InfraredSensor {
  private:
  public:
    InfraredSensor();
    void Init();
    int GetValue();
};

#endif
