#include "trafficlight.h"

TrafficLight::TrafficLight(int light_index, SluiceTCPHandler& handler)
    : light_index(light_index), handler(&handler)
{ }

bool TrafficLight::Red()
{
    bool success[2] = //this is to try avoid optimization, make sure all statements are executed
    {
        handler->SetTrafficLight(light_index, LightColorGreen, LightColorStateOff),
        handler->SetTrafficLight(light_index, LightColorRed, LightColorStateOn)
    };
    return success[0] && success[1];
}

bool TrafficLight::Green()
{
    bool success[2] =
    {
        handler->SetTrafficLight(light_index, LightColorRed, LightColorStateOff),
        handler->SetTrafficLight(light_index, LightColorGreen, LightColorStateOn)
    };
    return success[0] && success[1];
}

bool TrafficLight::Off()
{
    bool success[2] =
    {
        handler->SetTrafficLight(light_index, LightColorRed, LightColorStateOff),
        handler->SetTrafficLight(light_index, LightColorGreen, LightColorStateOff)
    };
    return success[0] && success[1];
}

LightColor TrafficLight::GetColor()
{
    if(handler->GetTrafficLight(light_index, LightColorGreen) == LightColorStateOn)
    {
        return LightColorGreen;
    }
    else if(handler->GetTrafficLight(light_index, LightColorRed) == LightColorStateOn)
    {
        return LightColorRed;
    }
    return LightColorOff;
}
