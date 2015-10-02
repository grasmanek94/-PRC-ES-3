#include "HardwareControl.h"

HardwareControl::HardwareControl() 
{
}

/*
 * Een class kan geen twee interfaces implementeren die
 * hetzelfde genoemd zijn maar iets anders functioneel
 * moeten doen!!
 */

void HardwareControl::Change(SensorEnum input)
{
	if (input == iSensor::Ultrasonic)
	{
		Input = new UltrasonicSensor();
		//Input->Init();
		inMode = 0;
	}

	if (input == iSensor::Infrared)
	{
		Input = new InfraredSensor();
		//Input->Init();
		inMode = 1;
	}

	if (input == iSensor::Serialp && !Serial)
	{
		Input = new SerialInput();
		//Input->Init();
		inMode = 2;
	}
}

void HardwareControl::Change(ERGBOutput output)
{
	if (output == iRgb::Led) 
	{
		Output = new RgbLed();
		//Output->Init();
		outMode = 0;
	}

	if (output == iRgb::Serialp && !Serial)
	{
		Output = new SerialOutput();
		//Output->Init();
		outMode = 1;
	}
}

void HardwareControl::SetColor(int hue)
{
	Output->SetColor(hue);
}

int HardwareControl::GetValue()
{
	Input->GetValue();
}