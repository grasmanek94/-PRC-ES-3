#ifndef RGBLED_H
#define RGBLED_H
#include <Arduino.h>
#include "iRgb.h"

class RgbLed : public iRgb
{
private:
	int rpin;
	int gpin;
	int bpin;
	void calculateRGB(int hue, int *rgb);
public:
	RgbLed();
	//void Init();
	void SetColor(int hue);
};

#endif
