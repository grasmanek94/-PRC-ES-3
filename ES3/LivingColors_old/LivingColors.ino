#include "HardwareControl.h"
#include "ISensor.h"
#include "IRgb.h"
#include "UltrasonicSensor.h"
#include "InfraredSensor.h"
#include "SerialInput.h"
#include "RgbLed.h"
#include "SerialOutput.h"

int usPin;
int irPin;
int rPin;
int gPin;
int bPin;

HardwareControl hw;
//UltrasonicSensor us(usPin);
//InfraredSensor ir(irPin);
SerialInput sinput;
//RgbLed rgb(rPin, gPin, bPin);
SerialOutput sout;

void setup() {
}

void loop() {
  hw.ReadSensor(&sinput);
  hw.WriteValue(&sout);
}

