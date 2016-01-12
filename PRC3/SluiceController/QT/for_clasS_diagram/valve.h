#ifndef VALVE_H
#define VALVE_H

#include "sluicetcphandler.h"

class Valve
{
private:
    EDoor door;
    int valve_index;
    SluiceTCPHandler* handler;
public:
    Valve(EDoor door, int valve_index, SluiceTCPHandler& handler);
    bool Open();
    bool Close();
    GetValveState GetState();
};

#endif // VALVE_H
