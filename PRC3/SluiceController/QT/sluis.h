#ifndef SLUIS_H
#define SLUIS_H

#include "sluicetcphandler.h"
#include "door.h"

class Sluis
{
private:
    Door low;
    Door high;
    SluiceTCPHandler* handler;
public:
    Sluis(SluiceTCPHandler& handler);

    WaterLevel GetWaterLevel();
    Door* DoorLow();
    Door* DoorHigh();
};

#endif // SLUIS_H
