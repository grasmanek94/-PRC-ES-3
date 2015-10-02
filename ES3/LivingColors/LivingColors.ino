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
