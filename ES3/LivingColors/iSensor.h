#ifndef ISENSOR_H
#define ISENSOR_H

enum SensorType
{
	Ultrasonic,
	Infrared,
	Serialp
};

class iSensor
{
private:
public:

	//virtual void Init() = 0;
	virtual int GetValue() = 0;
};

#endif
