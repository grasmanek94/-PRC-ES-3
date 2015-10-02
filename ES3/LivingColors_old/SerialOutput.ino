#include "SerialOutput.h"

SerialOutput::SerialOutput(){
  Serial.begin(9600);
}

void SerialOutput::SetColor(int hue){
  SetRGB(hue);
  Serial.println(String("R: ") + red + "G: " + green + "B: " + blue);
}

