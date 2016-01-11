#ifndef SLUICETCPHANDLER_H
#define SLUICETCPHANDLER_H
#include <QString>
#include <QObject>

//fuck QT
//#include <QtWebSockets/QWebSocket>
//Use our own WebSockets impl.:
#include "websocketclient.h"

#include "bimap.h"
using codeproject::bimap;

const unsigned short SLUIS_BASE_PORT = 5555;

enum Door
{
    DoorLeft,
    DoorRight
};

extern bimap<QString, Door> DoorMaps;
enum DoorState
{
    DoorStateOpen,
    DoorStateClose,
    DoorStateStop
};

extern bimap<QString, DoorState> DoorStateMaps;

enum ValveState
{
    ValveStateOpen,
    ValveStateClose,
    ValveStateMakingHalfLife3//should never happen
};

enum GetValveState
{
    GetValveStateOpen,
    GetValveStateClosed
};

extern bimap<QString, ValveState> ValveStateMaps;

enum GetDoorState
{
    GetDoorStateLocked,
    GetDoorStateClosed,
    GetDoorStateOpen,
    GetDoorStateClosing,
    GetDoorStateOpening,
    GetDoorStateStopped,
    GetDoorStateDamaged
};

extern bimap<QString, GetDoorState> GetDoorStateMaps;

enum LightColor
{
    LightColorRed,
    LightColorGreen
};

extern bimap<QString, LightColor> LightColorMaps;

enum WaterLevel
{
    WaterLevelLow,
    WaterLevelBelowValve2,
    WaterLevelAboveValve2,
    WaterLevelAboveValve3,
    WaterLevelHigh
};

extern bimap<QString, WaterLevel> WaterLevelMaps;

enum DoorLockState
{
    SetDoorLockStateOn,
    SetDoorLockStateOff,

    GetDoorLockStateWorking,
    GetDoorLockStateDamaged
};

extern bimap<QString, DoorLockState> DoorLockStateMaps;

enum LightColorState
{
    LightColorStateOn,
    LightColorStateOff
};

extern bimap<QString, LightColorState> LightColorStateMaps;

class SluiceTCPHandler : public QObject
{
    Q_OBJECT
private:
    WebSocketClient webSocket;
    bool connected;
    unsigned short port;
public:
    SluiceTCPHandler(unsigned short sluisnumber, QObject *parent = Q_NULLPTR);
    ~SluiceTCPHandler();

    bool SetDoor(Door which_door, DoorState which_state);
    GetDoorState GetDoor(Door which_door);
    bool SetDoorValve(Door which_door, unsigned int which_valve, ValveState which_state);
    ValveState GetDoorValve(Door which_door, unsigned int which_valve);
    bool SetTrafficLight(unsigned int which_light, LightColor which_color, LightColorState on);
    LightColorState GetTrafficLight(unsigned int which_light, LightColor which_color);
    WaterLevel GetWaterLevel();
    bool SetDoorLock(Door which_door, DoorLockState lock_state);
    DoorLockState GetDoorLockState(Door which_door);
    bool Connect();
};

#endif // SLUICETCPHANDLER_H
