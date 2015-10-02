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

	void Change(SensorType sensor);
	void Change(ERGBOutput output);

	void SetColor(int hue);
	int GetValue();

	SensorType GetInputMode();
	ERGBOutput GetOutputMode();

private:
	iSensor* Input;
	iRgb* Output;

	SensorType inMode;
	SensorType inMode_last;
	ERGBOutput outMode;
	ERGBOutput outMode_last;
};

#endif
