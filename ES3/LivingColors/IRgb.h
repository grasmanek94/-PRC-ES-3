#ifndef IRGB_H
#define IRGB_H

#include <Arduino.h>

class IRgb {
  private:
  public:
    int red;
    int green;
    int blue;

    void SetRGB(int hue)
    {
      float fhue = (float)hue;
      red = constrain(0.0234*fhue*fhue-8.4228*fhue+686.47, 0, 255);
      green = constrain(-0.0234*fhue*fhue+5.6142*fhue-10.729, 0, 255);
      blue = constrain(-0.0234*fhue*fhue+11.228*fhue-1021.3, 0, 255);
    }
    virtual void SetColor(int hue);
};

#endif


