#include "HardwareControl.h"

HardwareControl::HardwareControl() {
}

/*
 * Een class kan geen twee interfaces implementeren die
 * hetzelfde genoemd zijn maar iets anders functioneel
 * moeten doen!!
 */

void HardwareControl::InitS(ESensor sensor){
	if (sensor == iSensor::Ultrasonic) {
		Input = new UltrasonicSensor();
                Input->Init(TRIGPIN, ECHOPIN);
		inMode = 0;
	}
	
	if (sensor == iSensor::Infrared) {
		Input = new InfraredSensor();
                Input->Init(irpin);
		inMode = 1;
	}
	
	if (sensor == iSensor::Serialp && !Serial) {
		Input = new SerialInput();
                Input->Init(baudrate);
		inMode = 2;
	}
}

void HardwareControl::InitO(EOutput output){
	if (output == iRgb::Led) {
		Output = new RgbLed();
                Output->Init(rpin, gpin, bpin);
		outMode = 0;
	}
	
	if (output == iRgb::Serialp && !Serial) {
		Output = new SerialOutput();
                Output->Init(baudrate);
		outMode = 1;
	}
}

void HardwareControl::SetColor(int hue) {
	Output->SetColor(hue);
}

int HardwareControl::GetValue() {
	Input->GetValue();
}

void HardwareControl::SetPins(int r, int g, int b) {
  rpin = r;
  gpin = g;
  bpin = b;
}

void HardwareControl::SetBaudrate(int baud) {
  baudrate = baud;
}

void HardwareControl::SetIrPin(int pin) {
  irpin = pin;
}

void HardwareControl::SetUsPins(int TRIGPIN, int ECHOPIN) {
  TRIGPIN = TRIGPIN;
  ECHOPIN = ECHOPIN;
}

