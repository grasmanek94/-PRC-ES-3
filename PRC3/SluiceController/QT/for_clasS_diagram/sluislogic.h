#ifndef SLUISLOGIC_H
#define SLUISLOGIC_H

#include "sluicetcphandler.h"
#include "sluis.h"

enum State {
    StateIdle,
    StateInvarenLaag,
    StateSchuttenOmhoog,
    StateUitvarenHoog,
    StateInvarenHoog,
    StateSchuttenOmlaag,
    StateUitvarenLaag
};

class SluisLogic
{
private:
    SluiceTCPHandler handler;
    Sluis* sluis;
    void Tick();
public:
    SluisLogic(int nummer);
    ~SluisLogic();
    void Schutten();
    bool Vrijgeven_Uit();
    bool Vrijgeven_In();
    void Alarm();
    void Herstel();
private:
    State currentState;
    void alarmDoors(EDoor which);
    void redAll();
    bool checkValvesOpen(EDoor door);
};

#endif // SLUISLOGIC_H
