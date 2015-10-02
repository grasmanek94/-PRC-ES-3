#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(){
}

void UltrasonicSensor::Init() {
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}

int UltrasonicSensor::GetValue(){
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIGPIN, LOW);
  int  dist = pulseIn(ECHOPIN, HIGH);
  if (dist > 1800)
  {
    dist = 1800;
  }
  
  return map(dist, 0, 1800, 0, 360);
}
