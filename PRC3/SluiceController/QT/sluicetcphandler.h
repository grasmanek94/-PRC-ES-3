#ifndef SLUICETCPHANDLER_H
#define SLUICETCPHANDLER_H
#include <QString>
#include <QObject>
#include <QtWebSockets/QWebSocket>

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
    DoorLockStateWorking,
    DoorLockStateDamaged
};

extern bimap<QString, DoorLockState> DoorLockStateMaps;

class SluiceTCPHandler : public QObject
{
    Q_OBJECT
private:
    QWebSocket webSocket;
//private Q_SLOTS:
//    void Connected();
//    void Disconnected();

public:
    SluiceTCPHandler(unsigned short sluisnumber, QObject *parent = Q_NULLPTR);
    ~SluiceTCPHandler();

    void SetDoor(Door which_door, DoorState which_state);
    GetDoorState GetDoor(Door which_door);
    void SetDoorValve(Door which_door, unsigned int which_valve, ValveState which_state);
    ValveState GetDoorValve(Door which_door, unsigned int which_valve);
    void SetTrafficLight(unsigned int which_light, LightColor which_color, bool on);
    bool GetTrafficLight(unsigned int which_light, LightColor which_color);
    WaterLevel GetWaterLevel();
    void SetDoorLock(Door which_door, bool on);
    DoorLockState GetDoorLockState(Door which_door);
};

#endif // SLUICETCPHANDLER_H
