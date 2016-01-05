#include "sluicetcphandler.h"

#include <QMessageBox>
#include <QThread>
#include <QTime>

bimap<QString, Door> DoorMaps;
bimap<QString, DoorState> DoorStateMaps;
bimap<QString, ValveState> ValveStateMaps;
bimap<QString, GetDoorState> GetDoorStateMaps;
bimap<QString, LightColor> LightColorMaps;
bimap<QString, WaterLevel> WaterLevelMaps;
bimap<QString, DoorLockState> DoorLockStateMaps;

int maps_initialized = 0;

void InitMaps()
{
    if(maps_initialized)
    {
        return;
    }

    maps_initialized = 1;

    DoorMaps["Left"] = DoorLeft;
    DoorMaps["Right"] = DoorRight;

    DoorStateMaps["open"] = DoorStateOpen;
    DoorStateMaps["close"] = DoorStateClose;
    DoorStateMaps["stop"] = DoorStateStop;

    ValveStateMaps["open"] = ValveStateOpen;
    ValveStateMaps["close"] = ValveStateClosed;
    ValveStateMaps["hl3"] = ValveStateMakingHalfLife3;

    GetDoorStateMaps["doorLocked"] = GetDoorStateLocked;
    GetDoorStateMaps["doorClosed"] = GetDoorStateClosed;
    GetDoorStateMaps["doorOpen"] = GetDoorStateOpen;
    GetDoorStateMaps["doorClosing"] = GetDoorStateClosing;
    GetDoorStateMaps["doorOpening"] = GetDoorStateOpening;
    GetDoorStateMaps["doorStopped"] = GetDoorStateStopped;
    GetDoorStateMaps["motorDamage"] = GetDoorStateDamaged;

    LightColorMaps["Red"] = LightColorRed;
    LightColorMaps["Green"] = LightColorGreen;

    WaterLevelMaps["low"] = WaterLevelLow;
    WaterLevelMaps["belowValve2"] = WaterLevelBelowValve2;
    WaterLevelMaps["aboveValve2"] = WaterLevelAboveValve2;
    WaterLevelMaps["aboveValve3"] = WaterLevelAboveValve3;
    WaterLevelMaps["high"] = WaterLevelHigh;

    DoorLockStateMaps["lockWorking"] = DoorLockStateWorking;
    DoorLockStateMaps["lockDamaged"] = DoorLockStateDamaged;
}

SluiceTCPHandler::SluiceTCPHandler(unsigned short sluisnumber, QObject *parent)
    : QObject(parent), fetcher(SLUIS_BASE_PORT+sluisnumber)
{
    InitMaps();
}

SluiceTCPHandler::~SluiceTCPHandler()
{

}

void SluiceTCPHandler::SetDoor(Door which_door, DoorState which_state)
{
    QString query("SetDoor" + DoorMaps[which_door] + ":" + DoorStateMaps[which_state]);

    QMessageBox msgBox;
    msgBox.setText("RET OF: " + query);
    msgBox.setInformativeText(fetcher.SendDataAndGetReply(query));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

GetDoorState SluiceTCPHandler::GetDoor(Door which_door)
{
    return GetDoorStateClosed;
}

void SluiceTCPHandler::SetDoorValve(Door which_door, unsigned int which_valve, ValveState which_state)
{

}

ValveState SluiceTCPHandler::GetDoorValve(Door which_door, unsigned int which_valve)
{
    return ValveStateClosed;
}

void SluiceTCPHandler::SetTrafficLight(unsigned int which_light, LightColor which_color, bool on)
{

}

bool SluiceTCPHandler::GetTrafficLight(unsigned int which_light, LightColor which_color)
{

}

WaterLevel SluiceTCPHandler::GetWaterLevel()
{
    return WaterLevelLow;
}

void SluiceTCPHandler::SetDoorLock(Door which_door, bool on)
{

}

DoorLockState GetDoorLockState(Door which_door)
{
    return DoorLockStateDamaged;
}
