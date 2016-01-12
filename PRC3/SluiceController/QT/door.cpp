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
      outside(door == DoorLeft ? 1 : /*DoorRight*/ 4, handler),
      inside (door == DoorLeft ? 2 : /*DoorRight*/ 3, handler),
      low(door, 1, handler),
      mid(door, 2, handler),
      high(door, 3, handler),
      handler(&handler)
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
    return handler->SetDoor(door, DoorStateOpen);
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

bool Door::Alarm()
{
    bool s[4] =
    {
        ValveLow()->Close(),
        ValveMid()->Close(),
        ValveHigh()->Close(),
        Stop()
    };
    return s[0] && s[1] && s[2] && s[3];
}
