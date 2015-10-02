#ifndef ISENSOR_H
#define ISENSOR_H

class iSensor
{
private:
public:
	enum ESensor
	{
		Ultrasonic,
		Infrared,
		Serialp
	};
	//virtual void Init() = 0;
	virtual int GetValue() = 0;
};

typedef iSensor::ESensor SensorEnum;
#endif
