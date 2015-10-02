#include "HardwareControl.h"

HardwareControl* latest;

unsigned long debouncePrevIn = 0;
unsigned long debouncePrevOut = 0;

void UpdateInput()
{
	if (debouncePrevIn + 200 < millis())
	{
		latest->Change((SensorType)(digitalRead(2) + digitalRead(3) * 2 + digitalRead(4) * 4));
		debouncePrevIn = millis();
	}
}

void UpdateOutput()
{
	if (debouncePrevOut + 200 < millis())
	{
		latest->Change((ERGBOutput)digitalRead(5));
		debouncePrevOut = millis();
	}
}

// ISR on pins 2,3,4,5: change in/out mode
ISR(PCINT21_vect)
{
	UpdateOutput();
}

ISR(PCINT20_vect)
{
	UpdateInput();
}

ISR(PCINT19_vect)
{
	UpdateInput();
}

ISR(PCINT18_vect)
{
	UpdateInput();
}


HardwareControl::HardwareControl() 
{
	cli();
	// Enable interrupt on pis 2,3,4,5
	PCMSK2 |= _BV(PCINT21);  // Enable pin 5
	PCMSK2 |= _BV(PCINT20);  // Enable pin 4
	PCMSK2 |= _BV(PCINT19);  // Enable pin 3
	PCMSK2 |= _BV(PCINT18);  // Enable pin 2
	PCIFR |= _BV(PCIF2);    // Enable PCINT16-23
	PCICR |= _BV(PCIE2);    // Enable Change interrupt
	sei();

	Change(SensorType::Serialp);
	Change(ERGBOutput::Serialp);

	latest = this;
}

/*
 * Een class kan geen twee interfaces implementeren die
 * hetzelfde genoemd zijn maar iets anders functioneel
 * moeten doen!!
 */

void HardwareControl::Change(SensorType input)
{
	switch (input)
	{
		case SensorType::Ultrasonic:
			Input = new UltrasonicSensor();
			//Input->Init();
			break;
		case SensorType::Infrared:
			Input = new InfraredSensor();
			//Input->Init();
			break;
		case SensorType::Serialp:
			Input = new SerialInput();
			//Input->Init();
			break;
	}

	inMode = input;
	inMode_last = input;
}

void HardwareControl::Change(ERGBOutput output)
{
	switch (output)
	{
		case iRgb::Led:
			Output = new RgbLed();
			//Output->Init();
			break;
		case iRgb::Serialp:
			Output = new SerialOutput();
			//Output->Init();
			break;
	}

	outMode = output;
	outMode_last = output;
}

void HardwareControl::SetColor(int hue)
{
	Output->SetColor(hue);
}

int HardwareControl::GetValue()
{
	Input->GetValue();
}

SensorType HardwareControl::GetInputMode()
{
	return inMode;
}

ERGBOutput HardwareControl::GetOutputMode()
{
	return outMode;
}