#ifndef SLUIS_H
#define SLUIS_H

#include <QObject>
#include <QTimer>
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

class Sluis : public QObject
{
    Q_OBJECT
private:
    SluiceTCPHandler handler;
    QTimer ticker;
private Q_SLOTS:
    void Tick();
public:
    Sluis(int nummer, QObject *parent = NULL);
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
