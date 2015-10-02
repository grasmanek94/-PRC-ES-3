#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int pin):ISensor(_Min, _Max) {
  _Min = 0;
  _Max = 1023;
  pin = pin;
}

int UltrasonicSensor::GetMin(){
  return _Min;
}

int UltrasonicSensor::GetMax(){
  return _Max;
}

int UltrasonicSensor::GetValue(){
  return analogRead(pin);
}

