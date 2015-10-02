/*
	Pins 2,3 - Input Mode in bits:
		LOW LOW  - Ultrasonic
		LOW HIGH - Infrared
		HIGH LOW - Serial

	Pin 4 - Output Mode in bits:
		LOW  - LED
		HIGH - Serial


*/

#include "HardwareControl.h"

HardwareControl* control;

void setup()
{
	control = new HardwareControl();
}

void loop()
{
	control->SetColor(control->GetValue());
}
