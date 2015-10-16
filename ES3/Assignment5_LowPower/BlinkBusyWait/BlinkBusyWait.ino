#include <avr/sleep.h>

/*
 * Prescaler:
 * 0x00 = 1
 * 0x01 = 2
 * 0x02 = 4
 * 0x03 = 8
 * 0x04 = 16
 * 0x05 = 32
 * 0x06 = 64
 * 0x07 = 128
 * 0x08 = 256
 */

//int prescaler = 0x00;

ISR(SIG_WATCHDOG_TIMEOUT) {
  
}

void setup() {

  WDTCSR |= _BV(WDCE) | _BV(WDE);  // Watchdog Change Enable
  WDTCSR = 0x00 | _BV(WDE) | _BV(WDP3);
  //WDTCSR = _BV(WDE) | _BV(WDP3); // 4 seconds
  
  ADCSRA &= ~_BV(ADEN); // turn off the ADC
  ACSR |= _BV(ACD);     // disable the analog comparator
  DIDR1 |= _BV(AIN1D) | _BV(AIN0D); // disable digital input buffer on AIN1/0
  DIDR0 |= 0x3F;        // disable digital input buffers on ADC0-ADC5
  PRR |= 0xFF;          // power reduction reg: ALL!

  pinMode(13, OUTPUT);
}

/*  
 *  Het verlagen van de kloksnelheid is uiteindelijk
 *  toch handmatig gedaan wegens een trage multimeter.
 *  Met handmatige controle kan een stabielere waarde
 *  worden uitgelezen en opgeschreven.
 */
void loop() {
  cli();
  // Change prescaler
  CLKPR = 0x80;
  CLKPR = 0x08;
  //CLKPR = prescaler;
  sei();
  /*
  prescaler++;
  if (prescaler > 0x08) {
    prescaler = 0;
  }
  */
  
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  my_delay(369800/pow(2,CLKPR));              // wait for a second * 5
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  my_delay(369800/pow(2,CLKPR));              // wait for a second * 5

  SMCR |= _BV(SE) | _BV(SM1); //enable sleep and set power down
  sleep_cpu(); //call cpu sleep
}

// 369800 gives about 1s
// 1849000 is 5 then
void my_delay(volatile long duration){
  for (volatile long i = 0; i < duration; i++) {
    // Waste power!
  }
  //Serial.println(millis());
}

