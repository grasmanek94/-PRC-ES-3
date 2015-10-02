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

class HardwareControl : public iRgb, public iSensor
{
public:
	HardwareControl();
	void Init(SensorEnum sensor);
	void Init(ERGBOutput output);
	void SetColor(int hue);
	int GetValue();

private:
	iSensor* Input;
	iRgb* Output;
	int inMode;
	int outMode;
	int hue;
	int rgb[3];
};

#endif
