#ifndef Led_H
#define Led_H
#include "Timer.h"
#include <Arduino.h>

class Led 
{
public:
  Led(int pin);
  ~Led();

  void On();
  void Off();
  void Blink(float frequency);
  void beActive(); // must be NON BLOCKING!!!
 
private:
  // add whatever you need
  void HandleEvent(/* ....*/);
  Timer mytimer;

  int LedPin;
  int BlinkTime;
};

#endif

