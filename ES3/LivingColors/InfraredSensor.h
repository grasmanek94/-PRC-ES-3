#ifndef INFRAREDSENSOR_H
#define INFRAREDSENSOR_H
#include <Arduino.h>
#include "iSensor.h"

#define IR_PIN (9)

class InfraredSensor: public iSensor
{
private:
public:
	InfraredSensor();
	void Init();
	int GetValue();
};

#endif
