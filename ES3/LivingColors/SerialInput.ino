#include "SerialInput.h"


SerialInput::SerialInput():ISensor(_Min, _Max) {
  Serial.begin(9600);
  _Min = 0;
  _Max = 359;
}

int SerialInput::GetMin() {
 return _Min;
}

int SerialInput::GetMax() {
  return _Max;
}

int SerialInput::GetValue() {
  String input = "";
  while (Serial.available()){
    input += Serial.read();  
  }
  return input.toInt();
}

