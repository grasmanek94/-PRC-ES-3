#include "Timer.h"

Timer::Timer()
  : running(false)
{
}

void Timer::Start(unsigned long waitingtime)
{
  timeout = waitingtime;
  startTime = millis();
  running = true;
}

bool Timer::Elapsed()
{
  bool elapsed = false;
  if (!running)
  {
    return false;  // if we're not running, we cannot be elapsed
  }
  
  elapsed = (millis()-startTime > timeout);
  if (elapsed)
  { 
    running = false; // we're oneshot, so we dont restart automagically
  }
  return elapsed;
}



