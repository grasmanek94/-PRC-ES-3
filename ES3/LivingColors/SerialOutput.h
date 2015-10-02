#ifndef SERIALOUTPUT_H
#define SERIALOUTPUT_H
#include <Arduino.h>

#define OUT_BAUDRATE 9600

class SerialOutput {
  private:
    void calculateRGB(int hue, int *rgb);
  public:
    SerialOutput();
    void Init();
    void SetColor(int hue);
};

#endif