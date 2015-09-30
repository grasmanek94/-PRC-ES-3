#ifndef SERIALOUTPUT_H
#define SERIALOUTPUT_H

#include "IRgb.h"

class SerialOutput: public IRgb {
  private:
  public:
    SerialOutput();
    void SetColor(int hue);
};

#endif
