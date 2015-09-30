#include "RgbLed.h"

RgbLed::RgbLed(int pinr, int ping, int pinb) {
  pinMode(pinr, OUTPUT);
  pinMode(ping, OUTPUT);
  pinMode(pinb, OUTPUT);
}

void RgbLed::SetColor(int hue) {
  SetRGB(hue);
  analogWrite(pinr, red);
  analogWrite(pinr, green);
  analogWrite(pinr, blue);
}

