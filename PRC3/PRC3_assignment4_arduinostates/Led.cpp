#include "Led.h"


Led::Led(int pin)
{
// put your code here
  LedPin = pin;
  pinMode(LedPin, OUTPUT); // set hardware off to match te state
}

Led::~Led()
{
  //nothing for now
}

void Led::On() {
// put your code here
}

void Led::Off() 
{
// put your code here
}

void Led::Blink(float frequency) {

  BlinkTime = (unsigned long) 1000.0/frequency;
// put your code here
}

void Led::beActive()
{
  // here we poll the time, if it is elapsed we will generate an event
  if (mytimer.Elapsed())
  {
    // put your code here
  }
}
void Led::HandleEvent(/* ???*/)
{
 // put your code here
}


















