/*
 * Zoals de klasse diagram er nu staat snap ik niks van dit verhaal.
 * LivingColors kent enkel iRgb en iSensor.
 * HardwareControl implementeert de interface iRgb en iSensor.
 * Kan dit? Een interface kan enkel worden geïmplementeerd en kan
 * niet worden geïnstancieerd. Wat wél kan, is dat HardwareControl iets
 * iets implementeert, waarna je een nieuwe iRgb ding kunt maken van een
 * object HardwareControl. Misschien dat dit zo wel de bedoeling is,
 * maar deze toepassing heb ik zo moeten vinden op internet, dit hebben
 * we niet aangeleerd gekregen dacht ik.
 * 
 * In ieder geval, dit betekent dus dat je geen HardwareControl object
 * heb, maar HardwareControl gebruik je dus wel om een iRgb object te
 * maken? Dus iets als iRgb rgb = new HardwareControl(); en dan bij
 * rgb.Init(Sensor::led); geef je aan dat het een LED betreft (enum).
 */

#include "iSensor.h"
#include "iRgb.h"
#include "UltrasonicSensor.h"

#include "HardwareControl.h"

iSensor *sensor;
iRgb *rgb;

int inMode = 1;   // 1 US, 2 IR, 3 Serial
int outMode = 1;  // 1 RGB, 2 Serial
unsigned long debouncePrevIn = 0;
unsigned long debouncePrevOut = 0;

// ISR on pin 4 and pin 2: change in/out mode
ISR(PCINT20_vect) {
  if (debouncePrevIn + 200 < millis()) {
    inMode++;
    if (inMode > 2) {
      inMode = 1;
    }
    debouncePrevIn = millis();
  }
}

ISR(PCINT18_vect) {
  if (debouncePrevOut + 200 < millis()) {
    outMode++;
    if (outMode > 3) {
      outMode = 1;
    }
    debouncePrevOut = millis();
  }
}

void setup() {
	// todo: re
  	sensor = sinput;
  	out = sout;
  
	cli();
	// Enable interrupt on pin 4 and pin 2
	PCMSK2 |= _BV(PCINT20);  // Enable pin 4
	PCMSK2 |= _BV(PCINT18);  // Enable pin 2
	PCIFR  |= _BV(PCIF2);    // Enable PCINT16-23
	PCICR  |= _BV(PCIE2);    // Enable Change interrupt
	sei();
}

void loop() {
	switch (inMode) {
		case 1: // US
      delete sensor;
			sensor = new UltrasonicSensor();
      sensor->Init();
			break;
		case 2: // IR
			sensor = ir;
			break;
		case 3: // Serial
			sensor = sinput;
			break;
		default: // Default to serial
			sensor = sinput;
			break;
	}
	switch (outMode) {
		case 1: // RGB
			out = rgb;
			break;
		case 2: // serial
			out = sout;
			break;
		default: // Default to serial
			out = sout;
			break;
	}
	out->SetColor(sensor->GetValue());
}


