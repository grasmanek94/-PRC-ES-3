#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H
#include "iSensor.h"
#include "iRgb.h"
#include "UltrasonicSensor.h"
#include "InfraredSensor.h"
#include "SerialInput.h"
#include "RgbLed.h"
#include "SerialOutput.h"
#include <Arduino.h>

class HardwareControl : public iRgb, public iSensor {
  public:
    HardwareControl();
    void InitS(Sensor sensor);
    void InitO(Output output);
    void SetColor(int hue);
    int GetValue();
    void SetPins(int r, int g, int b);
    void SetBaudrate(int baud);
    void SetIrPin(int pin);
    void SetUsPins(int TRIGPIN, int ECHOPIN);
    
  private:
    iSensor* Input;
    iRgb* Output;
    int inMode;
    int outMode;
    int rpin;
    int gpin;
    int bpin;
    int irpin;
    int TRIGPIN;
    int ECHOPIN;  	
    int baudrate;
    int hue;
    int rgb[3];
};

#endif
