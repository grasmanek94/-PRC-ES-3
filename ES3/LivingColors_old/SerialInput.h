#ifndef SERIALINPUT_H
#define SERIALINPUT_H

#include "ISensor.h"

class SerialInput: public ISensor {
  private:
    int _Min;
    int _Max;
  public:
    SerialInput();
    int GetValue();
    int GetMin();
    int GetMax();
};

#endif
