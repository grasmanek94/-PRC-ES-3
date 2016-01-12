#include "door.h"

/*
Traffic lights, doors and valves:

                Left(Low)  Right(High)
             outside | inside | outside
                    1|2      3|4   ~~~~High Water~~~~
                   HI|GH    HI|GH  ~~~~~~~~~~~~~~~~~~
                   MI|D     MI|D   ~~~~~~~~~~~~~~~~~~
~~~~Low Water~~~~  LO|W     LO|W   ~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~    |        |    ~~~~~~~~~~~~~~~~~~
*/

Door::Door(EDoor door, SluiceTCPHandler& handler)
    : door(door),
      outside(door == DoorLeft ? 1 : /*DoorRight*/ 4, handler),//1V  ^4
      inside (door == DoorLeft ? 2 : /*DoorRight*/ 3, handler),//2V>>^3
      low(door, 1, handler),
      mid(door, 2, handler),
      high(door, 3, handler),
      handler(&handler),
      needed_level_to_open(door == DoorLeft ? WaterLevelLow : WaterLevelHigh)
{ }

TrafficLight* Door::LightInside()
{
    return &inside;
}

TrafficLight* Door::LightOutside()
{
    return &outside;
}

Valve* Door::ValveLow()
{
    return &low;
}

Valve* Door::ValveMid()
{
    return &mid;
}

Valve* Door::ValveHigh()
{
    return &high;
}

bool Door::Open()
{
    if(handler->GetWaterLevel() == needed_level_to_open)
    {
        return handler->SetDoor(door, DoorStateOpen);
    }
    return false;
}

bool Door::Close()
{
    return handler->SetDoor(door, DoorStateClose);
}

bool Door::Stop()
{
    return handler->SetDoor(door, DoorStateStop);
}

GetDoorState Door::GetState()
{
    return handler->GetDoor(door);
}
