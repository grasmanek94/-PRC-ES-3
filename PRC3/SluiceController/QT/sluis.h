#ifndef SLUIS_H
#define SLUIS_H

#include "sluicetcphandler.h"

enum State {
    StateIdle,
    StateInvarenLaag,
    StateSchuttenOmhoog,
    StateUitvarenHoog,
    StateInvarenHoog,
    StateSchuttenOmlaag,
    StateUitvarenLaag
};

class Sluis
{
    SluiceTCPHandler handler;
public:
    Sluis(int nummer);
    //QString VerplaatsBoot();
    void Schutten();
    bool Vrijgeven_Uit();
    bool Vrijgeven_In();
    void Alarm();
    void Herstel();
private:
    State currentState;
    void alarmDoors(Door which);

};

#endif // SLUIS_H
