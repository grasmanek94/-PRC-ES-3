#include "sluis.h"

Sluis::Sluis(SluisTCPHandler& handler)
    : handler(&handler), low(DoorLeft, handler), high(DoorRight, handler)
{ }

WaterLevel Sluis::GetWaterLevel()
{
    return handler->GetWaterLevel();
}

Door* Sluis::DoorLow()
{
    return &low;
}

Door* Sluis::DoorHigh()
{
    return &high;
}
