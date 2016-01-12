#include "valve.h"

Valve::Valve(EDoor door, int valve_index, SluiceTCPHandler& handler)
    : door(door), valve_index(valve_index), handler(&handler)
{ }

bool Valve::Open()
{
    return handler->SetDoorValve(door, valve_index, SetValveStateOpen);
}

bool Valve::Close()
{
    return handler->SetDoorValve(door, valve_index, SetValveStateClose);
}

GetValveState Valve::GetState()
{
    return handler->GetDoorValve(door, valve_index);
}
