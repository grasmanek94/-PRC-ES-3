#ifndef RGBLED_H
#define RGBLED_H
#include <Arduino.h>
#include "iRgb.h"

#define RGB_LED_PINR (5)
#define RGB_LED_PING (6)
#define RGB_LED_PINB (9)

class RgbLed : public iRgb
{
private:
	void calculateRGB(int hue, int *rgb);
public:
	RgbLed();
	//void Init();
	void SetColor(int hue);
};

#endif
