#include "Led.h"


Led::Led(int pin) {
// put your code here
  LedPin = pin;
  pinMode(LedPin, OUTPUT); // set hardware off to match te state
}

Led::~Led() {
  //nothing for now
}

void Led::On() {
// put your code here
  digitalWrite(LedPin, HIGH);
  
}

void Led::Off() {
// put your code here
  digitalWrite(LedPin, LOW);
}

void Led::Blink(float frequency) {

  BlinkTime = (unsigned long) 1000.0/frequency;
// put your code here
  mytimer.Start(BlinkTime);
}

void Led::beActive() {
  // here we poll the time, if it is elapsed we will generate an event
  if (mytimer.Elapsed()) {
    // put your code here
    HandleEvent();
    mytimer.Start(BlinkTime);
  }
}
void Led::HandleEvent(/* ???*/) {
 // put your code here
 if (digitalRead(LedPin)) {
    Off();
    //Serial.println(String("Off: ") + LedPin);
  }
  else {
    On();
    //Serial.println(String("On: ") + LedPin);
  }
}

