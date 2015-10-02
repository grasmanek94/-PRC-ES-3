#include "InfraredSensor.h"

InfraredSensor::InfraredSensor(){
}

void InfraredSensor::Init(){
}

int InfraredSensor::GetValue() {
  return map(analogRead(pin), 0, 1023, 0, 360);
}

