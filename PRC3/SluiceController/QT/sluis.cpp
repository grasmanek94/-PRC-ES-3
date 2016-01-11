#include "sluis.h"
#include "sluicetcphandler.h"

#include <QMessageBox>
void qinfo(QString a, QString b)
{
    QMessageBox msgBox;
    msgBox.setText("RET OF: " + a);
    msgBox.setInformativeText(b);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

Sluis::Sluis(int nummer, QObject *parent)
    : QObject(parent), handler(nummer), ticker(this)
{
    currentState = StateIdle;
    connect(&ticker, &QTimer::timeout, this, &Sluis::Tick);
    ticker.setInterval(100);
    ticker.start();
}

void Sluis::Tick()
{
    //qinfo("tick", "lol");
    static WaterLevel previous_waterlevel;

    if(currentState == StateSchuttenOmlaag)
    {
        WaterLevel level = handler.GetWaterLevel();
        //if(previous_waterlevel != level)
        //{
            switch(level)
            {
                case WaterLevelHigh:
                case WaterLevelAboveValve3:
                case WaterLevelAboveValve2:
                case WaterLevelBelowValve2:
                {
                    handler.SetDoorValve(DoorLeft, 1, SetValveStateOpen);
                    break;
                }
                case WaterLevelLow:
                {
                    handler.SetDoorValve(DoorLeft, 1, SetValveStateClose);
                    handler.SetDoorValve(DoorLeft, 2, SetValveStateClose);
                    handler.SetDoorValve(DoorLeft, 3, SetValveStateClose);
                    handler.SetDoor(DoorLeft, DoorStateOpen);
                }
                break;

                default:
                    level = previous_waterlevel;
                break;
            }
        //    previous_waterlevel = level;
        //}
    }
    else if(currentState == StateSchuttenOmhoog)
    {
        WaterLevel level = handler.GetWaterLevel();
        //if(previous_waterlevel != level)
        //{
            switch(level)
            {
                case WaterLevelLow:
                {
                    handler.SetDoorValve(DoorRight, 1, SetValveStateOpen);
                }
                break;

                case WaterLevelBelowValve2:
                {
                    handler.SetDoorValve(DoorRight, 2, SetValveStateOpen);
                }
                break;

                case WaterLevelAboveValve3:
                case WaterLevelAboveValve2:
                {
                    handler.SetDoorValve(DoorRight, 3, SetValveStateOpen);
                }
                break;

                case WaterLevelHigh:
                {
                    handler.SetDoorValve(DoorRight, 3, SetValveStateClose);
                    handler.SetDoorValve(DoorRight, 2, SetValveStateClose);
                    handler.SetDoorValve(DoorRight, 1, SetValveStateClose);
                    handler.SetDoor(DoorRight, DoorStateOpen);
                }
                break;
                default:
                    level = previous_waterlevel;
                break;
            }
            //previous_waterlevel = level;
        //}
    }
}

bool Sluis::Vrijgeven_In()
{
    WaterLevel level = handler.GetWaterLevel();
    GetDoorState leftDoorState = handler.GetDoor(DoorLeft);
    GetDoorState rightDoorState = handler.GetDoor(DoorRight);

    if (currentState == StateUitvarenLaag && level == WaterLevelLow)
    {
        if (!checkValvesOpen(DoorRight))// && leftDoorState == GetDoorStateClosed)
        {
            handler.SetDoor(DoorLeft, DoorStateOpen);
        }
        if (leftDoorState == GetDoorStateOpen)
        {
            currentState = StateInvarenLaag;
            handler.SetTrafficLight(1, LightColorGreen, LightColorStateOn);
            handler.SetTrafficLight(1, LightColorRed, LightColorStateOff);
            handler.SetTrafficLight(2, LightColorGreen, LightColorStateOff);
            handler.SetTrafficLight(2, LightColorRed, LightColorStateOn);
            return true;
        }
    }

    if (currentState == StateUitvarenHoog && level == WaterLevelHigh)
    {
        if (!checkValvesOpen(DoorLeft))// && rightDoorState == GetDoorStateOpen)
        {
            handler.SetDoor(DoorRight, DoorStateOpen);
        }
        if (rightDoorState == GetDoorStateOpen)
        {
            currentState = StateInvarenHoog;
            handler.SetTrafficLight(3, LightColorGreen, LightColorStateOff);
            handler.SetTrafficLight(3, LightColorRed, LightColorStateOn);
            handler.SetTrafficLight(4, LightColorGreen, LightColorStateOn);
            handler.SetTrafficLight(4, LightColorRed, LightColorStateOff);
            return true;
        }

    }

    return false;
}

bool Sluis::Vrijgeven_Uit()
{
    WaterLevel level = handler.GetWaterLevel();
    GetDoorState leftDoorState = handler.GetDoor(DoorLeft);
    GetDoorState rightDoorState = handler.GetDoor(DoorRight);


    if (level == WaterLevelLow)// && leftDoorState == GetDoorStateClosed)
    {
        handler.SetDoor(DoorLeft, DoorStateOpen);
    }
    if (level == WaterLevelHigh)// && rightDoorState == GetDoorStateOpen)
    {
        handler.SetDoor(DoorRight, DoorStateOpen);
    }

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
        handler.SetTrafficLight(3, LightColorGreen, LightColorStateOn);
        handler.SetTrafficLight(3, LightColorRed, LightColorStateOff);
        handler.SetTrafficLight(4, LightColorGreen, LightColorStateOff);
        handler.SetTrafficLight(4, LightColorRed, LightColorStateOn);
        return true;
    }
    return false;
}


void Sluis::Schutten() //todo: deuren
{
    WaterLevel level = handler.GetWaterLevel();

    // Water omhoog
    if (level == WaterLevelLow)
    {
        redAll();
        handler.SetDoor(DoorLeft, DoorStateClose);
        currentState = StateSchuttenOmhoog;
        /*if (level != WaterLevelHigh)
        {
            handler.SetDoor(DoorLeft, DoorStateClose);
            if (handler.GetDoor(DoorLeft) == GetDoorStateClosed)
            {
                handler.SetDoorValve(DoorRight, 1, SetValveStateOpen);
                if (level == WaterLevelAboveValve2)
                {
                    handler.SetDoorValve(DoorRight, 2, SetValveStateOpen);
                }
                if (level == WaterLevelAboveValve3)
                {
                    handler.SetDoorValve(DoorRight, 3, SetValveStateOpen);
                }
            }
        }
        if (level == WaterLevelHigh)
        {
            handler.SetDoorValve(DoorRight, 1, SetValveStateClose);
            handler.SetDoorValve(DoorRight, 2, SetValveStateClose);
            handler.SetDoorValve(DoorRight, 3, SetValveStateClose);
            handler.SetDoor(DoorRight, DoorStateOpen);
        }*/
    }

    // Water omlaag
    if (level == WaterLevelHigh)
    {
        redAll();
        handler.SetDoor(DoorRight, DoorStateClose);
        currentState = StateSchuttenOmlaag;
        /*if (level != WaterLevelLow)
        {
            handler.SetDoor(DoorRight, DoorStateClose);
            handler.SetDoorValve(DoorRight, 1, SetValveStateClose);
            handler.SetDoorValve(DoorRight, 2, SetValveStateClose);
            handler.SetDoorValve(DoorRight, 3, SetValveStateClose);
            if (handler.GetDoor(DoorRight) == GetDoorStateClosed)
            {
                handler.SetDoorValve(DoorLeft, 1, SetValveStateOpen);
            }
        }
        if (level == WaterLevelLow)
        {
            handler.SetDoorValve(DoorLeft, 1, SetValveStateClose);
            handler.SetDoorValve(DoorLeft, 2, SetValveStateClose);
            handler.SetDoorValve(DoorLeft, 3, SetValveStateClose);
            handler.SetDoor(DoorLeft, DoorStateOpen);
        }*/
    }
}

void Sluis::redAll()
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

void Sluis::Alarm()
{
    redAll();
    alarmDoors(DoorLeft);
    alarmDoors(DoorRight);
}

void Sluis::alarmDoors(Door which)
{
        handler.SetDoorValve(which, 1, SetValveStateClose);
        handler.SetDoorValve(which, 2, SetValveStateClose);
        handler.SetDoorValve(which, 3, SetValveStateClose);
        handler.SetDoor(which, DoorStateStop);
}

bool Sluis::checkValvesOpen(Door door)
{
    for (int i=0; i < 3; i++)
    {
        if (GetValveState(door) == GetValveStateOpen)
        {
            return true;
        }
    }
    return false
}

void Sluis::Herstel()
{

}
