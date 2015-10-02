#ifndef SERIALINPUT_H
#define SERIALINPUT_H
#include <Arduino.h>

#define IN_BAUDRATE 9600

class SerialInput {
  private:
  public:
    SerialInput();
    void Init();
    int GetValue();
};

#endif
