#include "sluis.h"
#include "sluicetcphandler.h"

Sluis::Sluis(int nummer)
    : handler(nummer)
{

}

QString Sluis::VerplaatsBoot()
{
    WaterLevel level = handler.GetWaterLevel();
    if(level == WaterLevelLow)
    {
        if(handler.SetDoor(DoorLeft, DoorStateClose))
        {
            if(handler.SetDoorValve(DoorRight, 1, ValveStateOpen))
            {
//boot gaat omhoog
            }
            else
            {
//error
            }
        }
        else
        {
//error
        }
    } else if(level == WaterLevelHigh)
    {
        if(handler.SetDoor(DoorRight, DoorStateClose))
        {
            if(handler.SetDoorValve(DoorLeft, 3, ValveStateOpen))
            {
//boot gaat omlaag
            }
            else
            {
//error
            }
        }
        else
        {
//error
        }
    } else
    {
//al bezig
    }
}
