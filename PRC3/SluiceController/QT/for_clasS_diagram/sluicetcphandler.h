#ifndef SLUICETCPHANDLER_H
#define SLUICETCPHANDLER_H

#include "websocketclient.h"

enum EDoor
{
    Door_UNKNOWN_ERROR,
    DoorLeft,
    DoorRight
};

enum DoorState
{
    DoorState_UNKNOWN_ERROR,
    DoorStateOpen,
    DoorStateClose,
    DoorStateStop,
};

enum SetValveState
{
    SetValveState_UNKNOWN_ERROR,
    SetValveStateOpen,
    SetValveStateClose
};

enum GetValveState
{
    GetValveState_UNKNOWN_ERROR,
    GetValveStateOpen,
    GetValveStateClosed
};

enum GetDoorState
{
    GetDoorState_UNKNOWN_ERROR,
    GetDoorStateLocked,
    GetDoorStateClosed,
    GetDoorStateOpen,
    GetDoorStateClosing,
    GetDoorStateOpening,
    GetDoorStateStopped,
    GetDoorStateDamaged
};

enum LightColor
{
    LightColor_UNKNOWN_ERROR,
    LightColorRed,
    LightColorGreen,
    LightColorOff
};

enum WaterLevel
{
    WaterLevel_UNKNOWN_ERROR,
    WaterLevelLow,
    WaterLevelBelowValve2,
    WaterLevelAboveValve2,
    WaterLevelAboveValve3,
    WaterLevelHigh
};

enum DoorLockState
{
    DoorLockState_UNKNOWN_ERROR,
    SetDoorLockStateOn,
    SetDoorLockStateOff,

    GetDoorLockStateWorking,
    GetDoorLockStateDamaged
};

enum LightColorState
{
    LightColorState_UNKNOWN_ERROR,
    LightColorStateOn,
    LightColorStateOff
};

class SluiceTCPHandler
{
private:
    WebSocketClient webSocket;
    bool connected;
    unsigned short port;
public:
    SluiceTCPHandler(unsigned short sluisnumber);
    ~SluiceTCPHandler();

    bool SetDoor(EDoor which_door, DoorState which_state);
    GetDoorState GetDoor(EDoor which_door);
    bool SetDoorValve(EDoor which_door, unsigned int which_valve, SetValveState which_state);
    GetValveState GetDoorValve(EDoor which_door, unsigned int which_valve);
    bool SetTrafficLight(unsigned int which_light, LightColor which_color, LightColorState on);
    LightColorState GetTrafficLight(unsigned int which_light, LightColor which_color);
    WaterLevel GetWaterLevel();
    bool SetDoorLock(EDoor which_door, DoorLockState lock_state);
    DoorLockState GetDoorLockState(EDoor which_door);
    bool Connect();
};

#endif // SLUICETCPHANDLER_H
