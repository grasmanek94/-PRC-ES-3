#ifndef SLUIS_H
#define SLUIS_H

#include "sluicetcphandler.h"

class Sluis
{
    SluiceTCPHandler handler;
public:
    Sluis(int nummer);
    QString VerplaatsBoot();
};

#endif // SLUIS_H
