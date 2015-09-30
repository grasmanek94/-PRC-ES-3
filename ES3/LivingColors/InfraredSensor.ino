#include "InfraredSensor.h"


InfraredSensor::InfraredSensor(int pin): ISensor(_Min, _Max){
  pin = pin;
  _Min = 0;
  _Max = 1023;
}

int InfraredSensor::GetMin() {
 return _Min;
}

int InfraredSensor::GetMax() {
  return _Max;
}

int InfraredSensor::GetValue() {
  return analogRead(pin);
}

