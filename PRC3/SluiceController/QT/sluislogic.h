#ifndef SLUISLOGIC_H
#define SLUISLOGIC_H

#include <QObject>
#include <QTimer>
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

class SluisLogic : public QObject
{
    Q_OBJECT
private:
    SluiceTCPHandler handler;
    QTimer ticker;
    Sluis* sluis;
private Q_SLOTS:
    void Tick();
public:
    SluisLogic(int nummer, QObject *parent = NULL);
    ~SluisLogic();
    //QString VerplaatsBoot();
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
