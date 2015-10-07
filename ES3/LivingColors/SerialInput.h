#ifndef SERIALINPUT_H
#define SERIALINPUT_H
#include <Arduino.h>
#include "iSensor.h"
#define IN_BAUDRATE 9600

class SerialInput : public iSensor
{
private:
	int lastKnown;
public:
	SerialInput();
	//void Init();
	int GetValue();
};

#endif
