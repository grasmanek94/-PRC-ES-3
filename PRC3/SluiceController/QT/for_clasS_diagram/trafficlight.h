#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "sluicetcphandler.h"

class TrafficLight
{
private:
    int light_index;
    SluiceTCPHandler* handler;
public:
    TrafficLight(int light_index, SluiceTCPHandler& handler);
    bool Red();
    bool Green();
    bool Off();
    LightColor GetColor();
};

#endif // TRAFFICLIGHT_H
