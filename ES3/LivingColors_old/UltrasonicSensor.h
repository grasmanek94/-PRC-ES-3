#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include "ISensor.h"

class UltrasonicSensor: public ISensor {
  private:
    int _Min;
    int _Max;
    int pin;
  public:
    UltrasonicSensor(int pin);
    int GetValue();
    int GetMin();
    int GetMax();
};

#endif
