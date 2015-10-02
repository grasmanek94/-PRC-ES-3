#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H
#include <Arduino.h>

class UltrasonicSensor {
  private:
    int pin;
  public:
    UltrasonicSensor();
    void Init();
    int GetValue();
};

#endif
