#include "sluis.h"

Sluis::Sluis(SluiceTCPHandler& handler)
{ }

WaterLevel Sluis::GetWaterLevel()
{
	return false;
}

Door* Sluis::DoorLow()
{
	return false;
}

Door* Sluis::DoorHigh()
{
	return false;
}
