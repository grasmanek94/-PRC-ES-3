#ifndef SLUICETCPHANDLER_H
#define SLUICETCPHANDLER_H
#include <QString>
#include <QTcpSocket>
#include <QNetworkSession>

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
    ValveStateClosed,
    ValveStateMakingHalfLife3//should never happen
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

enum LightState
{
    LightStateRed,
    LightStateGreen
};

extern bimap<QString, LightState> LightStateMaps;

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
    DoorLockStateWorking,
    DoorLockStateDamaged
};

extern bimap<QString, DoorLockState> DoorLockStateMaps;

class SluiceTCPHandler
{
private:

    QTcpSocket *tcpSocket;
    QNetworkSession *networkSession;

    void connected();
public:
    SluiceTCPHandler(unsigned short sluisnumber);
    ~SluiceTCPHandler();

    void SetDoor(Door which_door, DoorState which_state);
    GetDoorState GetDoor(Door which_door);
    void SetDoorValve(Door which_door, unsigned int which_valve, ValveState which_state);
    ValveState GetDoorValve(Door which_door, unsigned int which_valve);
    void SetTrafficLight(unsigned int which_light, LightState which_state);
    LightState GetTrafficLight(unsigned int which_light);
    WaterLevel GetWaterLevel();
    void SetDoorLock(Door which_door, bool on);
    DoorLockState GetDoorLockState(Door which_door);
};

#endif // SLUICETCPHANDLER_H
