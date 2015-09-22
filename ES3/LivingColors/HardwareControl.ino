#include "HardwareControl.h"
#include "ISensor.h"
#include "IRgb.h"
#include "UltrasonicSensor.h"
#include "InfraredSensor.h"
#include "SerialInput.h"
#include "RgbLed.h"
#include "SerialOutput.h"

HardwareControl::HardwareControl() {
  Serial.begin(9600);
}

HardwareControl::WriteValue(int value) {

}

HardwareConrol::ReadSensor(Type type) {
  if (type == Type.Ultrasonic) {
    
  }
  if (type == Type.Infrared) {
    
  }
}
