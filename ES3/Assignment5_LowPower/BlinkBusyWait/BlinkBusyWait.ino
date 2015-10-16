void setup() {
  cli();
  ADCSRA &= ~_BV(ADEN); //turn off the ADC
  ACSR |= _BV(ACD); //Disable the analog comparator
  DIDR1 |= _BV(AIN1D) | _BV(AIN0D); //Disable digital input buffer on AIN1/0
  DIDR0 |= 0x3F; //Disable digital input buffers on ADC0-ADC5
  PRR |= 0xFF; //Power reduction reg: ALL!
  sei();
  
  pinMode(13, OUTPUT);
}

void loop() {

  
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  my_delay(1849000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  my_delay(1849000);              // wait for a second
}

// 369800 gives about 1s
// 1849000 is 5 then
void my_delay(volatile long duration){
  for (volatile long i = 0; i < duration; i++) {
    // Waste power!
  }
  //Serial.println(millis());
}

