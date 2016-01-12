#ifndef SLUISLOGIC_H
#define SLUISLOGIC_H

#include <QObject>
#include <QTimer>
#include "sluicetcphandler.h"
#include "sluis.h"

//chronological order
enum State
{
/* V */StateIdle,
/* V */StateWaitingForVrijgeven,
/* V */StateVrijgegeven,//<-----<-----<------<------<-----<---+
/* V */StateSchuttenUp,  //either this one or the one below   |
/* V */StateSchuttenDown,//either this one or the one above   ^
/* V */StateWaitingForUitvarenVrijgeven,//                    |
/* > */StateVrijgegevenForUitvaren,//->------>------>----->---+
};

enum AlarmLevel
{
    AlarmLevelDisabled,
    AlarmLevelDispatched,
    AlarmLevelSafetyEnsured
};

class SluisLogic : public QObject
{
    Q_OBJECT
private:
    SluiceTCPHandler handler;
    QTimer ticker;
    Sluis* sluis;
    int alarm_level;

    void TickIdle();
    void TickSchutten();
    void TickAlarm();
private Q_SLOTS:
    void Tick();
public:
    SluisLogic(int nummer, QObject *parent = NULL);
    ~SluisLogic();
    bool Schutten();
    bool Vrijgeven();
    void Alarm();
    bool Herstel();
private:
    State currentState;
};

#endif // SLUISLOGIC_H
