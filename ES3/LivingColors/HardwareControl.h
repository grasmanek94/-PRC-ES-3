#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H
#include "ISensor.h"
#include "IRgb.h"
#include "UltrasonicSensor.h"
#include "InfraredSensor.h"
#include "SerialInput.h"
#include "RgbLed.h"
#include "SerialOutput.h"

class HardwareControl {
  public:
    HardwareControl();

    void WriteValue(IRgb* out);
    void ReadSensor(ISensor* sensor);
    
  private:
    IRgb* out;
    ISensor* sensor;
    int hue;
};

#endif
