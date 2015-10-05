#ifndef Timer_H
#define Timer_H
#include <Arduino.h>

class Timer {
public:
  Timer();

  /**
    * Starts the timer with the parameter time.
    * Clients can check if the time has passed by calling Elapsed method
   */
  void Start(/* time in msecs */unsigned long time);

  /**
   * returns true if the timeperiod set by Start has passed.
   * Otherwise false
   */
  bool Elapsed();

private:
  unsigned long startTime;
  unsigned long timeout;
  bool running;
};

#endif


