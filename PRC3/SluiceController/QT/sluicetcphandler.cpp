#include "sluicetcphandler.h"

#include <QMessageBox>

bimap<QString, Door> DoorMaps;
bimap<QString, DoorState> DoorStateMaps;
bimap<QString, ValveState> ValveStateMaps;
bimap<QString, GetDoorState> GetDoorStateMaps;
bimap<QString, LightState> LightStateMaps;
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
    DoorMaps["Right"] =DoorRight;

    DoorStateMaps["open"] =DoorStateOpen;
    DoorStateMaps["close"] =DoorStateClose;
    DoorStateMaps["stop"] =DoorStateStop;

    ValveStateMaps["open"] =ValveStateOpen;
    ValveStateMaps["close"] =ValveStateClosed;
    ValveStateMaps["hl3"] =ValveStateMakingHalfLife3;

    GetDoorStateMaps["doorLocked"] =GetDoorStateLocked;
    GetDoorStateMaps["doorClosed"] =GetDoorStateClosed;
    GetDoorStateMaps["doorOpen"] =GetDoorStateOpen;
    GetDoorStateMaps["doorClosing"] =GetDoorStateClosing;
    GetDoorStateMaps["doorOpening"] =GetDoorStateOpening;
    GetDoorStateMaps["doorStopped"] =GetDoorStateStopped;
    GetDoorStateMaps["motorDamage"] =GetDoorStateDamaged;

    LightStateMaps["Red"] =LightStateRed;
    LightStateMaps["Green"] =LightStateGreen;

    WaterLevelMaps["low"] =WaterLevelLow;
    WaterLevelMaps["belowValve2"] =WaterLevelBelowValve2;
    WaterLevelMaps["aboveValve2"] =WaterLevelAboveValve2;
    WaterLevelMaps["aboveValve3"] =WaterLevelAboveValve3;
    WaterLevelMaps["high"] =WaterLevelHigh;

    DoorLockStateMaps["lockWorking"] =DoorLockStateWorking;
    DoorLockStateMaps["lockDamaged"] =DoorLockStateDamaged;
}

SluiceTCPHandler::SluiceTCPHandler(unsigned short sluisnumber)
    : tcpSocket(NULL), networkSession(NULL)
{
    InitMaps();

    tcpSocket = new QTcpSocket(NULL);
    tcpSocket->connectToHost("localhost", SLUIS_BASE_PORT+sluisnumber);
    tcpSocket->waitForConnected();
}

SluiceTCPHandler::~SluiceTCPHandler()
{
    tcpSocket->close();

    delete tcpSocket;
    tcpSocket = NULL;

    delete networkSession;
    networkSession = NULL;
}

void SluiceTCPHandler::SetDoor(Door which_door, DoorState which_state)
{
    QByteArray array;
    array.append(QString("SetDoor") + DoorMaps[which_door] + ":" + DoorStateMaps[which_state]);
    if(tcpSocket->write(array) != -1)
    {
        //while(!tcpSocket->bytesAvailable() < 3)
        //{}
    }
    array = tcpSocket->readAll();
    QString response(array);

    QMessageBox msgBox;
    msgBox.setText(QString("RESULT OF: ") + "SetDoor" + DoorMaps[which_door] + ":" + DoorStateMaps[which_state]);

    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    if(response != "ack")
    {
        msgBox.setInformativeText(response);
        //throw std::exception();
    }
    else
    {
        msgBox.setInformativeText(response);
    }
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

void SluiceTCPHandler::SetTrafficLight(unsigned int which_light, LightState which_state)
{
    QByteArray array;
    array.append(QString("SetTrafficLight") + which_light + ":" + DoorStateMaps[which_state]);
    if(tcpSocket->write(array) != -1)
    {
        //while(!tcpSocket->bytesAvailable() < 3)
        //{}
    }
    array = tcpSocket->readAll();
    QString response(array);

    QMessageBox msgBox;
    msgBox.setText(QString("RESULT OF: ") + "SetDoor" + DoorMaps[which_door] + ":" + DoorStateMaps[which_state]);

    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    if(response != "ack")
    {
        msgBox.setInformativeText(response);
        //throw std::exception();
    }
    else
    {
        msgBox.setInformativeText(response);
    }
    msgBox.exec();
}

LightState SluiceTCPHandler::GetTrafficLight(unsigned int which_light)
{
    return LightStateRed;
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
