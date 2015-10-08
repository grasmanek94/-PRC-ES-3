#include "SerialOutput.h"

SerialOutput::SerialOutput()
{
	//if (!Serial)
	Serial.begin(OUT_BOUDRATE);
}

//void SerialOutput::Init()
//{
//	//if (!Serial)
//	Serial.begin(OUT_BOUDRATE);
//}

void SerialOutput::SetColor(int hue)
{
	int rgb[3];
	calculateRGB(hue, rgb);
	String s =	"R: " + String(rgb[0], 10) +
				" G: " + String(rgb[1], 10) +
				" B: " + String(rgb[2], 10);
	Serial.println(s);
}

void SerialOutput::calculateRGB(int hue, int *rgb)
{
	float fhue = (float)hue;
	rgb[0] = (int)constrain(0.0234*fhue*fhue - 8.4228*fhue + 686.47, 0.0, 255.0);
	rgb[1] = (int)constrain(-0.0234*fhue*fhue + 5.6142*fhue - 10.729, 0.0, 255.0);
	rgb[2] = (int)constrain(-0.0234*fhue*fhue + 11.228*fhue - 1021.3, 0.0, 255.0);
}
