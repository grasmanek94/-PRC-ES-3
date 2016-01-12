#ifndef DOOR_H
#define DOOR_H

#include "sluicetcphandler.h"
#include "trafficlight.h"
#include "valve.h"

class Door
{
private:
    EDoor door;
    TrafficLight outside;
    TrafficLight inside;
    Valve low;
    Valve mid;
    Valve high;
    SluiceTCPHandler* handler;
    WaterLevel needed_level_to_open;
public:
    Door(EDoor door, SluiceTCPHandler& handler);

    TrafficLight* LightInside();
    TrafficLight* LightOutside();

    Valve* ValveLow();
    Valve* ValveMid();
    Valve* ValveHigh();

    bool Open();
    bool Close();
    bool Stop();
    GetDoorState GetState();
};

#endif // DOOR_H