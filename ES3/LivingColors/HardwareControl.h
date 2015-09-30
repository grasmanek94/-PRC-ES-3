#include "ISensor.h"
#include "IRgb.h"
#include "UltrasonicSensor.h"
#include "InfraredSensor.h"
#include "SerialInput.h"
#include "RgbLed.h"
#include "SerialOutput.h"

enum Type {
  Ultrasonic,
  Infrared
};

class HardwareControl {
  public:
    HardwareControl();
    
    void WriteValue(int value);
    void ReadSensor(Type type)
    
  private:

};
