#ifndef INFRAREDSENSOR_H
#define INFRAREDSENSOR_H

#include "ISensor.h"

class InfraredSensor: public ISensor {
  private:
    int pin;
    int _Min;
    int _Max;
  public:
    InfraredSensor(int pin);
    int GetValue();
    int GetMin();
    int GetMax();
};

#endif
