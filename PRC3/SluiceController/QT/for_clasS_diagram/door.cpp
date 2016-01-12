#include "door.h"

Door::Door(EDoor door, SluiceTCPHandler& handler)
{ }

TrafficLight* Door::LightInside()
{
	return false;
}

TrafficLight* Door::LightOutside()
{
	return false;
}

Valve* Door::ValveLow()
{
	return false;
}

Valve* Door::ValveMid()
{
	return false;
}

Valve* Door::ValveHigh()
{
	return false;
}

bool Door::Open()
{
	return false;
}

bool Door::Close()
{
	return false;
}

bool Door::Stop()
{
	return false;
}

GetDoorState Door::GetState()
{
	return false;
}

bool Door::Alarm()
{
	return false;
}
