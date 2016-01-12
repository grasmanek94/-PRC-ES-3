#include "sluislogic.h"
#include "sluicetcphandler.h"

#include <QMessageBox>
void qinfo(QString a, QString b)
{
    QMessageBox msgBox;
    msgBox.setText("RET OF: " + a);
    msgBox.setInformativeText(b);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

SluisLogic::SluisLogic(int nummer, QObject *parent)
    : QObject(parent), handler(nummer), ticker(this), sluis(new Sluis(handler)), alarm_level(AlarmLevelDisabled)
{
    currentState = StateIdle;
    connect(&ticker, &QTimer::timeout, this, &SluisLogic::Tick);
    ticker.setInterval(100);
    ticker.start();
}

SluisLogic::~SluisLogic()
{
    delete sluis;
    sluis = NULL;
}

/*
1)	Knop Start -> shutten
2)	If water levels eq, close doors
3)	If eq water levels high, lower water, else higher water
4)	If doors open & vrijgegeven -> lights on green ( knop “vrijgeven voor uitvaren”)
5)	Door only open if water levels e.q.
6)	Only one level higher valve may open, else water goes too fast
7)	If water needs to go down, only lowest valve is opened.
8)	Alarm button. if both doors closed, close all valves. If doors opening or closing, immideately stop.
9)	Knop herstel after noodsituatie
10)	Left and right door may never be open at same time.
11)	Er zijn 3 sluizen in het complex, sommigen hebben aparte eigenschappen:
    Sluis op poort 5555 en 5556 (1 & 2): normale sluis, zoals hierboven beschreven
    Sluis op poort 5558 (4): deze sluis heeft andere motoren, deze blijven maar 1 seconde aan en moeten dus telkens opnieuw aangezet worden.
-> inherit form SluisLogic, eigenlijk zouden we van Deur moeten inheriten en de deur logica veranderen, MAAR, de hele werking/logica/alle gebeuren
is in SluisLogic dus daarvan moeten we inheriten en veranderen, wat ook perfect zal werken en helemaal goed is. Niet dat wat we willen maar wel een goede oplossing.
Alle logica is opgesplitst in kleine functies die makkelijk aan te passen zijn - PERFECT? Yeah!
*/
void SluisLogic::Tick()
{
    if(alarm_level == AlarmLevelDisabled)
    {
        switch(currentState)
        {
        case StateIdle:
            return TickIdle();
        case StateSchuttenDown:
        case StateSchuttenUp:
            return TickSchutten();
        default:
            break;
        }
    }
    else
    {
        TickAlarm();
    }
}

void SluisLogic::TickAlarm()
{
    if(alarm_level == AlarmLevelDispatched)
    {
        GetDoorState ls = sluis->DoorLow()->GetState();
        GetDoorState rs = sluis->DoorHigh()->GetState();
        if(ls == GetDoorStateClosed && rs == GetDoorStateClosed)
        {
            bool s[6] =
            {
                sluis->DoorLow()->ValveLow()->Close(),
                sluis->DoorLow()->ValveMid()->Close(),
                sluis->DoorLow()->ValveHigh()->Close(),
                sluis->DoorHigh()->ValveLow()->Close(),
                sluis->DoorHigh()->ValveMid()->Close(),
                sluis->DoorHigh()->ValveHigh()->Close()
            };
            if(s[0] && s[1] && s[2] && s[3] && s[4] && s[5])
            {
                alarm_level = AlarmLevelSafetyEnsured;
            }
        }
        else
        {
            //only in state ShuttenUp/Down
            bool s[2];
            if(ls == GetDoorStateClosing || ls == GetDoorStateOpening)
            {
                s[0] = sluis->DoorLow()->Stop();
            }
            else
            {
                s[0] = true;
            }

            if(rs == GetDoorStateClosing || rs == GetDoorStateOpening)
            {
                s[1] = sluis->DoorHigh()->Stop();
            }
            else
            {
                s[1] = true;
            }

            if(s[0] && s[1])
            {
                alarm_level = AlarmLevelSafetyEnsured;
            }
        }
    }
}

void SluisLogic::TickSchutten()
{
    if(currentState == StateSchuttenDown)
    {
        if(     sluis->GetWaterLevel() == WaterLevelLow &&
                sluis->DoorLow()->ValveLow()->Close() &&
                sluis->DoorLow()->Open())
        {
            currentState = StateWaitingForUitvarenVrijgeven;
        }
    }
    else if(currentState == StateSchuttenUp)
    {
        static WaterLevel old_level = WaterLevel_UNKNOWN_ERROR;
        WaterLevel level = sluis->GetWaterLevel();
        if(old_level != level)
        {
            switch(level)
            {
            case WaterLevelLow:
                if(sluis->DoorHigh()->ValveLow()->Open())
                {
                     old_level = level;
                }
                break;

            case WaterLevelBelowValve2:
                if(sluis->DoorHigh()->ValveMid()->Open())
                {
                     old_level = level;
                }
                break;

            case WaterLevelAboveValve2:
            case WaterLevelAboveValve3:
                if(sluis->DoorHigh()->ValveHigh()->Open())
                {
                     old_level = level;
                }
                break;

            case WaterLevelHigh:
                if(     sluis->DoorHigh()->ValveLow()->Close() &&
                        sluis->DoorHigh()->ValveMid()->Close() &&
                        sluis->DoorHigh()->ValveHigh()->Close() &&
                        sluis->DoorHigh()->Open())
                {
                    currentState = StateWaitingForUitvarenVrijgeven;
                }
                break;

            default:
                break;
            }


        }
    }
}

void SluisLogic::TickIdle()
{
    WaterLevel level = sluis->GetWaterLevel();
    if(level == WaterLevelLow)
    {
        if(sluis->DoorLow()->Open())
        {
            currentState = StateWaitingForVrijgeven;
        }
    }
    else if(level == WaterLevelHigh)
    {
        if(sluis->DoorHigh()->Open())
        {
            currentState = StateWaitingForVrijgeven;
        }
    }
}

bool SluisLogic::Vrijgeven()
{
    if(currentState == StateWaitingForVrijgeven || currentState == StateVrijgegevenForUitvaren)
    {
        WaterLevel level = sluis->GetWaterLevel();

        if(
            (level == WaterLevelLow && sluis->DoorLow()->LightOutside()->Green()) ||
            (level == WaterLevelHigh && sluis->DoorHigh()->LightOutside()->Green())
          )
        {
            if((currentState != StateVrijgegevenForUitvaren) ||
                (
                 (level == WaterLevelLow && sluis->DoorLow()->LightInside()->Red()) ||
                 (level == WaterLevelHigh && sluis->DoorHigh()->LightInside()->Red())
                ))
            {
                currentState = StateVrijgegeven;
                return true;
            }
        }
    }
    else if(currentState == StateWaitingForUitvarenVrijgeven)
    {
         WaterLevel level = sluis->GetWaterLevel();
         if(
             (level == WaterLevelHigh && sluis->DoorHigh()->LightInside()->Green() && sluis->DoorHigh()->Open()) ||
             (level == WaterLevelLow && sluis->DoorLow()->LightInside()->Green() && sluis->DoorLow()->Open())
           )
         {
            currentState = StateVrijgegevenForUitvaren;
            return true;
         }
    }
    return false;
}

bool SluisLogic::Schutten()
{
    WaterLevel level = sluis->GetWaterLevel();

    if(currentState == StateVrijgegeven)
    {
        if(level == WaterLevelLow)
        {
            if(     sluis->DoorLow()->Close() &&
                    sluis->DoorLow()->LightOutside()->Red() &&
                    sluis->DoorHigh()->ValveLow()->Open())
            {
                currentState = StateSchuttenUp;
                return true;
            }
        }
        else if(level == WaterLevelHigh)
        {
            if(     sluis->DoorHigh()->Close() &&
                    sluis->DoorHigh()->LightOutside()->Red() &&
                    sluis->DoorLow()->ValveLow()->Open())
            {
                currentState = StateSchuttenDown;
                return true;
            }
        }
    }
    return false;
}

void SluisLogic::Alarm()
{
    if(alarm_level == AlarmLevelDisabled)
    {
        alarm_level = AlarmLevelDispatched;
    }
}

bool SluisLogic::Herstel()
{
    if(alarm_level != AlarmLevelDisabled)
    {
        if(currentState == StateWaitingForUitvarenVrijgeven)
        {
            WaterLevel level = sluis->GetWaterLevel();
            if(level == WaterLevelLow)
            {
                if(     sluis->GetWaterLevel() == WaterLevelLow &&
                        sluis->DoorLow()->ValveLow()->Close() &&
                        sluis->DoorLow()->Open())
                {
                    alarm_level = AlarmLevelDisabled;
                    return true;
                }
            }
            else if(level == WaterLevelHigh)
            {
                if(     sluis->DoorHigh()->ValveLow()->Close() &&
                        sluis->DoorHigh()->ValveMid()->Close() &&
                        sluis->DoorHigh()->ValveHigh()->Close() &&
                        sluis->DoorHigh()->Open())
                {
                    alarm_level = AlarmLevelDisabled;
                    return true;
                }
            }
        }
    }
    return false;
}
