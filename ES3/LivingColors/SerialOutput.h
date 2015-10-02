#ifndef SERIALOUTPUT_H
#define SERIALOUTPUT_H
#include <Arduino.h>
#include "iRgb.h"
#define OUT_BOUDRATE 9600

class SerialOutput : public iRgb 
{
private:
	void calculateRGB(int hue, int *rgb);
public:
	SerialOutput();
	void Init();
	void SetColor(int hue);
};

#endif
