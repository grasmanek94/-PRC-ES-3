#include "SerialInput.h"

SerialInput::SerialInput()
{
	//if (!Serial) 
	Serial.begin(IN_BAUDRATE);
}

//void SerialInput::Init()
//{
//	//if (!Serial) 
//	Serial.begin(IN_BAUDRATE);
//}

int SerialInput::GetValue()
{
	if (Serial.available() > 0)
	{
		return Serial.parseInt();
	}
}
