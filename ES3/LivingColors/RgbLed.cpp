#include "RgbLed.h"

RgbLed::RgbLed() 
{
	pinMode(rpin, OUTPUT);
	pinMode(gpin, OUTPUT);
	pinMode(bpin, OUTPUT);
}

//void RgbLed::Init() 
//{
//	pinMode(rpin, OUTPUT);
//	pinMode(gpin, OUTPUT);
//	pinMode(bpin, OUTPUT);
//}

void RgbLed::SetColor(int hue) 
{
	int rgb[3];
	calculateRGB(hue, rgb);
	analogWrite(rpin, rgb[0]);
	analogWrite(gpin, rgb[1]);
	analogWrite(bpin, rgb[2]);
}

void RgbLed::calculateRGB(int hue, int *rgb) 
{
	float fhue = (float)hue;
	rgb[0] = constrain(0.0234*fhue*fhue - 8.4228*fhue + 686.47, 0, 255);
	rgb[1] = constrain(-0.0234*fhue*fhue + 5.6142*fhue - 10.729, 0, 255);
	rgb[2] = constrain(-0.0234*fhue*fhue + 11.228*fhue - 1021.3, 0, 255);
}
