#include "sluis.h"

Sluis::Sluis(SluiceTCPHandler& handler)
    : low(DoorLeft, handler), high(DoorRight, handler), handler(&handler)
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
