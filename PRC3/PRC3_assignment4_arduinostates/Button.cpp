#include "Button.h"
#include <Arduino.h>

Button::Button(int pin) {
  pinMode(ButtonPin, INPUT);
  ButtonPin = pin;
}

Button::~Button() {
  
}

bool Button::Pressed() {
  bool stat = false;
  if (digitalRead(ButtonPin))  {
    if (prevTime + 100 < millis()) {
      stat = true;
    }
    prevTime = millis();
  }
  return stat;
}

