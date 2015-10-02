/*
	Pins 2,3	- Input Mode in bits:
					LOW LOW  - Ultrasonic
					LOW HIGH - Infrared
					HIGH LOW - Serial

	Pin 4		- Output Mode in bits:
					LOW  - LED
					HIGH - Serial

	Pin 5,6,9	- Output pins for RGB

	Pin 7,8		- Ultrasonic control and input pins

	Pin A0		- InfraRed sensor input

	Serial Baud Rate - 9600
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
