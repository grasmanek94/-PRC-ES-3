#include "SerialInput.h"

SerialInput::SerialInput()
{
	//if (!Serial) 
	Serial.begin(IN_BAUDRATE);
	lastKnown = 0;
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
		while (Serial.peek() < '0' || Serial.peek() > '9')
		{
			if (Serial.read() == -1)
			{
				break;
			}
		}

		if (Serial.available() > 0)
		{
			lastKnown = Serial.parseInt();
		}

		while (Serial.available())//discard all remaining bytes
		{
			Serial.read();
		}
	}
	return lastKnown;
}
