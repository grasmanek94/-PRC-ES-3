#include "sluis.h"
#include "sluicetcphandler.h"

#include <QMessageBox>


Sluis::Sluis(int nummer)
    : handler(nummer)
{
    currentState = StateIdle;
}


bool Sluis::Vrijgeven_In()
{
    WaterLevel level = handler.GetWaterLevel();
    GetDoorState leftDoorState = handler.GetDoor(DoorLeft);
    GetDoorState rightDoorState = handler.GetDoor(DoorRight);
    /*ValveState valveState[6] =
    {
        handler.GetDoorValve(DoorLeft, 1),
        handler.GetDoorValve(DoorLeft, 2),
        handler.GetDoorValve(DoorLeft, 3),
        handler.GetDoorValve(DoorRight, 1),
        handler.GetDoorValve(DoorRight, 2),
        handler.GetDoorValve(DoorRight, 3)
    };
    for (int i = 0; i < 6; i++)
    {
        if (valveState[i] != ValveStateClosed)
        {
            return false;
        }
    }*/

    if (level == WaterLevelLow && leftDoorState == GetDoorStateClosed)
    {
        handler.SetDoor(DoorLeft, DoorStateOpen);
    }
    if (level == WaterLevelHigh && rightDoorState == GetDoorStateOpen)
    {
        handler.SetDoor(DoorLeft, DoorStateOpen);
    }


    if (level == WaterLevelLow && leftDoorState == GetDoorStateOpen)
    {
        currentState = StateInvarenLaag;
        handler.SetTrafficLight(1, LightColorGreen, LightColorStateOn);
        handler.SetTrafficLight(1, LightColorRed, LightColorStateOff);
        handler.SetTrafficLight(2, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(2, LightColorRed, LightColorStateOn);
        return true;

    }
    if (level == WaterLevelHigh && rightDoorState == GetDoorStateOpen)
    {
        currentState = StateInvarenHoog;
        handler.SetTrafficLight(3, LightColorGreen, LightColorStateOn);
        handler.SetTrafficLight(3, LightColorRed, LightColorStateOff);
        handler.SetTrafficLight(4, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(4, LightColorRed, LightColorStateOn);
        return true;
    }

    return false;
}

bool Sluis::Vrijgeven_Uit()
{
    WaterLevel level = handler.GetWaterLevel();
    GetDoorState leftDoorState = handler.GetDoor(DoorLeft);
    GetDoorState rightDoorState = handler.GetDoor(DoorRight);
    /*ValveState valveState[6] = {
        handler.GetDoorValve(DoorLeft, 1),
        handler.GetDoorValve(DoorLeft, 2),
        handler.GetDoorValve(DoorLeft, 3),
        handler.GetDoorValve(DoorRight, 1),
        handler.GetDoorValve(DoorRight, 2),
        handler.GetDoorValve(DoorRight, 3)
    };
    for (int i = 0; i < 6; i++){
        if (valveState[i] != ValveStateClosed) {
            return false;
        }
    }*/

    if (level == WaterLevelLow && leftDoorState == GetDoorStateOpen)
    {
        currentState = StateUitvarenLaag;
        handler.SetTrafficLight(1, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(1, LightColorRed, LightColorStateOn);
        handler.SetTrafficLight(2, LightColorGreen, LightColorStateOn);
        handler.SetTrafficLight(2, LightColorRed, LightColorStateOff);
        return true;
    }
    if (level == WaterLevelHigh && rightDoorState == GetDoorStateOpen)
    {
        currentState = StateUitvarenHoog;
        handler.SetTrafficLight(3, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(3, LightColorRed, LightColorStateOn);
        handler.SetTrafficLight(4, LightColorGreen, LightColorStateOn);
        handler.SetTrafficLight(4, LightColorRed, LightColorStateOff);
        return true;
    }
    return false;
}


void Sluis::Schutten()
{
    bool changeLights = false;
    WaterLevel level = handler.GetWaterLevel();

    if (currentState == StateInvarenLaag || currentState == StateUitvarenLaag)
    {
        changeLights = true;
        if (level != WaterLevelHigh)
        {
            handler.SetDoor(DoorLeft, DoorStateClose);
            if (handler.GetDoor(DoorLeft) == GetDoorStateClosed)
            {
                handler.SetDoorValve(DoorRight, 1, ValveStateOpen);
                if (level == WaterLevelAboveValve2)
                {
                    handler.SetDoorValve(DoorRight, 2, ValveStateOpen);
                }
                if (level == WaterLevelAboveValve3)
                {
                    handler.SetDoorValve(DoorRight, 3, ValveStateOpen);
                }
            }
        }
        if (level == WaterLevelHigh)
        {
            handler.SetDoorValve(DoorRight, 1, ValveStateClosed);
            handler.SetDoorValve(DoorRight, 2, ValveStateClosed);
            handler.SetDoorValve(DoorRight, 3, ValveStateClosed);
            handler.SetDoor(DoorRight, DoorStateOpen);
        }
    }
    if (currentState == StateInvarenHoog || currentState == StateUitvarenHoog)
    {
        changeLights = true;
        if (level != WaterLevelLow)
        {
            handler.SetDoor(DoorRight, DoorStateClose);
            handler.SetDoorValve(DoorRight, 1, ValveStateClosed);
            handler.SetDoorValve(DoorRight, 2, ValveStateClosed);
            handler.SetDoorValve(DoorRight, 3, ValveStateClosed);
            if (handler.GetDoor(DoorRight) == GetDoorStateClosed)
            {
                handler.SetDoorValve(DoorLeft, 1, ValveStateOpen);
            }
        }
        if (level == WaterLevelLow)
        {
            handler.SetDoorValve(DoorLeft, 1, ValveStateClosed);
            handler.SetDoorValve(DoorLeft, 2, ValveStateClosed);
            handler.SetDoorValve(DoorLeft, 3, ValveStateClosed);
            handler.SetDoor(DoorLeft, DoorStateOpen);
        }
    }
    if (changeLights)
    {
        handler.SetTrafficLight(1, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(1, LightColorRed, LightColorStateOn);
        handler.SetTrafficLight(2, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(2, LightColorRed, LightColorStateOn);
        handler.SetTrafficLight(3, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(3, LightColorRed, LightColorStateOn);
        handler.SetTrafficLight(4, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(4, LightColorRed, LightColorStateOn);
    }

/*
    if(level == WaterLevelLow)
    {

        if(handler.SetDoor(DoorLeft, DoorStateClose))
        {
            if(handler.SetDoorValve(DoorRight, 1, ValveStateOpen))
            {
                if (level == WaterLevelAboveValve2)
                {
                    if (handler.SetDoorValve(DoorRight, 1, ValveStateClosed))
                    {

                    }
                    if (handler.SetDoorValve(DoorRight, 2, ValveStateOpen))
                    {

                    }
                }
                if (level == WaterLevelHigh)
                {
                    if (handler.SetDoorValve(DoorRight, 2, ValveStateClosed))
                    {

                    }
                    if (handler.SetDoor(DoorRight, DoorStateOpen))
                    {

                    }
                }
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
    }
    else if(level == WaterLevelHigh)
    {
        if(handler.SetDoor(DoorRight, DoorStateClose))
        {
            if(handler.SetDoorValve(DoorLeft, 3, ValveStateOpen))
            {
                //boot gaat omlaag
                if (level == WaterLevelLow)
                {
                    if (handler.SetDoorValve(DoorLeft, 3, ValveStateClosed))
                    {

                    }
                    if (handler.SetDoor(DoorLeft, DoorStateOpen))
                    {

                    }
                }
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
    }
    else
    {
        //al bezig
    }
    */

}

void Sluis::Alarm()
{
    handler.SetTrafficLight(1, LightColorGreen, LightColorStateOff);
    handler.SetTrafficLight(1, LightColorRed, LightColorStateOn);
    handler.SetTrafficLight(2, LightColorGreen, LightColorStateOff);
    handler.SetTrafficLight(2, LightColorRed, LightColorStateOn);
    handler.SetTrafficLight(3, LightColorGreen, LightColorStateOff);
    handler.SetTrafficLight(3, LightColorRed, LightColorStateOn);
    handler.SetTrafficLight(4, LightColorGreen, LightColorStateOff);
    handler.SetTrafficLight(4, LightColorRed, LightColorStateOn);

    alarmDoors(DoorLeft);
    alarmDoors(DoorRight);

/*
    if (handler.GetDoor(DoorLeft) == GetDoorStateClosed)
    {
        handler.SetDoorValve(DoorLeft, 1, ValveStateClosed);
        handler.SetDoorValve(DoorLeft, 2, ValveStateClosed);
        handler.SetDoorValve(DoorLeft, 3, ValveStateClosed);
    }
    else
    {
        handler.SetDoor(DoorLeft, DoorStateStop);
    }

    if (handler.GetDoor(DoorRight) == GetDoorStateClosed)
    {
        handler.SetDoorValve(DoorRight, 1, ValveStateClosed);
        handler.SetDoorValve(DoorRight, 2, ValveStateClosed);
        handler.SetDoorValve(DoorRight, 3, ValveStateClosed);
    }
    else
    {
        handler.SetDoor(DoorLeft, DoorStateStop);
    }
*/

}

void Sluis::Herstel()
{

}

void Sluis::alarmDoors(Door which)
{
    if (handler.GetDoor(which) == GetDoorStateClosed)
    {
        handler.SetDoorValve(which, 1, ValveStateClosed);
        handler.SetDoorValve(which, 2, ValveStateClosed);
        handler.SetDoorValve(which, 3, ValveStateClosed);
    }
    else
    {
        handler.SetDoor(which, DoorStateStop);
    }
}
