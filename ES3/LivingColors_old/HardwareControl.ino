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

void HardwareControl::WriteValue(IRgb* out) {
  if (out) {
    out->SetColor(hue);
  }
}

void HardwareControl::ReadSensor(ISensor* sensor) {
  if (sensor) {
    int val = sensor->GetValue();
    hue = map(val, sensor->GetMin(), sensor->GetMax(), 0, 360);
  } else {
    hue = -1;
  }
}
