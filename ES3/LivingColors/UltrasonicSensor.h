#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H
#include <Arduino.h>
#include "iSensor.h"
#define TRIGPIN (7)
#define ECHOPIN (8)

class UltrasonicSensor: public iSensor 
{
  private:
    int pin;
  public:
    UltrasonicSensor();
    void Init();
    int GetValue();
};

#endif
