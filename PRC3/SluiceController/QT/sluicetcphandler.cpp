#include <QTime>

#include "websocketclient.h"
#include "sluicetcphandler.h"
#include "bimap.h"

bimap<QString, Door> DoorMaps;
bimap<QString, DoorState> DoorStateMaps;
bimap<QString, SetValveState> SetValveStateMaps;
bimap<QString, GetValveState> GetValveStateMaps;
bimap<QString, GetDoorState> GetDoorStateMaps;
bimap<QString, LightColor> LightColorMaps;
bimap<QString, WaterLevel> WaterLevelMaps;
bimap<QString, DoorLockState> DoorLockStateMaps;
bimap<QString, LightColorState> LightColorStateMaps;
//if we may not make our life convienient with C++11
//then this way it be.
void InitMaps()
{
    static int maps_initialized = 0;
    if(maps_initialized)
    {
        return;
    }

    maps_initialized = 1337;

    DoorMaps["Left"] = DoorLeft;
    DoorMaps["Right"] = DoorRight;

    DoorStateMaps["open"] = DoorStateOpen;
    DoorStateMaps["close"] = DoorStateClose;
    DoorStateMaps["stop"] = DoorStateStop;

    GetValveStateMaps["open"] = GetValveStateOpen;
    GetValveStateMaps["closed"] = GetValveStateClosed;

    SetValveStateMaps["open"] = SetValveStateOpen;
    SetValveStateMaps["close"] = SetValveStateClose;

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

    DoorLockStateMaps["lockWorking"] = GetDoorLockStateWorking;
    DoorLockStateMaps["lockDamaged"] = GetDoorLockStateDamaged;
    DoorLockStateMaps["on"] = SetDoorLockStateOn;
    DoorLockStateMaps["off"] = SetDoorLockStateOff;

    LightColorStateMaps["on"] = LightColorStateOn;
    LightColorStateMaps["off"] = LightColorStateOff;
}

SluiceTCPHandler::SluiceTCPHandler(unsigned short sluisnumber, QObject *parent)
    : QObject(parent)
{
    InitMaps();
    port = SLUIS_BASE_PORT+sluisnumber;
    Connect();
}

bool SluiceTCPHandler::Connect()
{
    connected = webSocket.connect(port);
    return connected;
}

SluiceTCPHandler::~SluiceTCPHandler()
{

}

bool SluiceTCPHandler::SetDoor(Door which_door, DoorState which_state)
{
    QString query("SetDoor%1:%2");
    query = query.arg(DoorMaps[which_door]).arg(DoorStateMaps[which_state]);

    webSocket.send(query);
    QString response = webSocket.readMessage();

    if(response.compare("ack") == 0)
    {
        return true;
    }
    return false;
}

GetDoorState SluiceTCPHandler::GetDoor(Door which_door)
{
    QString query("GetDoor%1");
    query = query.arg(DoorMaps[which_door]);

    webSocket.send(query);
    QString response = webSocket.readMessage();

    try
    {
        return GetDoorStateMaps[response];
    }
    catch(const bimap_base::value_not_found&)
    {
        return GetDoorState_UNKNOWN_ERROR;
    }
}

bool SluiceTCPHandler::SetDoorValve(Door which_door, unsigned int which_valve, SetValveState which_state)
{
    QString query("SetDoor%1Valve%2:%3");
    query = query.arg(DoorMaps[which_door]).arg(which_valve).arg(SetValveStateMaps[which_state]);

    webSocket.send(query);
    QString response = webSocket.readMessage();

    if(response.compare("ack") == 0)
    {
        return true;
    }
    return false;
}

GetValveState SluiceTCPHandler::GetDoorValve(Door which_door, unsigned int which_valve)
{
    QString query("GetDoor%1Valve%2");
    query = query.arg(DoorMaps[which_door]).arg(which_valve);

    webSocket.send(query);
    QString response = webSocket.readMessage();

    try
    {
        return GetValveStateMaps[response];
    }
    catch(const bimap_base::value_not_found&)
    {
        return GetValveState_UNKNOWN_ERROR;
    }
}

bool SluiceTCPHandler::SetTrafficLight(unsigned int which_light, LightColor which_color, LightColorState light_state)
{
    QString query("SetTrafficLight%1%2:%3");
    query = query.arg(which_light).arg(LightColorMaps[which_color]).arg(LightColorStateMaps[light_state]);

    webSocket.send(query);
    QString response = webSocket.readMessage();

    if(response.compare("ack") == 0)
    {
        return true;
    }
    return false;
}

LightColorState SluiceTCPHandler::GetTrafficLight(unsigned int which_light, LightColor which_color)
{
    QString query("GetTrafficLight%1%2");
    query = query.arg(which_light).arg(LightColorMaps[which_color]);

    webSocket.send(query);
    QString response = webSocket.readMessage();

    try
    {
        return LightColorStateMaps[response];
    }
    catch(const bimap_base::value_not_found&)
    {
        return LightColorState_UNKNOWN_ERROR;
    }
}

WaterLevel SluiceTCPHandler::GetWaterLevel()
{
    QString query("GetWaterLevel");

    webSocket.send(query);
    QString response = webSocket.readMessage();

    //qinfo(query, response);

    try
    {
        return WaterLevelMaps[response];
    }
    catch(const bimap_base::value_not_found&)
    {
        return WaterLevel_UNKNOWN_ERROR;
    }
}

bool SluiceTCPHandler::SetDoorLock(Door which_door, DoorLockState lock_state)
{
    QString query("SetDoorLock%1:%2");
    query = query.arg(DoorMaps[which_door]).arg(DoorLockStateMaps[lock_state]);

    webSocket.send(query);
    QString response = webSocket.readMessage();

    if(response.compare("ack") == 0)
    {
        return true;
    }
    return false;
}

DoorLockState SluiceTCPHandler::GetDoorLockState(Door which_door)
{
    QString query("GetDoorLockState%1");
    query = query.arg(DoorMaps[which_door]);

    webSocket.send(query);
    QString response = webSocket.readMessage();

    try
    {
        return DoorLockStateMaps[response];
    }
    catch(const bimap_base::value_not_found&)
    {
        return DoorLockState_UNKNOWN_ERROR;
    }
}
