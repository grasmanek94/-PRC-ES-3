/*
   Pins:  10    Port:  B2  Button
          12           B4  Button
          5            D5  LED
          6            D6  LED
          3            D3  Buzzer OCR2B
          
   Buttons: 10 & 12
   LEDs   : 5  & 6
   Buzzer : 3
   ($ARDUINO_DIR)/hardware/arduino/avr/cores/arduino/*
*/

void setup() {
  Serial.begin(9600);
  
  // Simultaneously set DDD5 and DDD6 as output
  // Also DDD3
  DDRD |= _BV(DDD5) | _BV(DDD6) | _BV(DDD3);
  
  // Set DDB2 DDB3 DDB4 as input
  DDRB  &= ~(_BV(DDB2) | _BV(DDB4) | _BV(DDB3));
  
  // Pullup bits
  PORTB |= _BV(PORTB2) | _BV(PORTB3) | _BV(PORTB4);
}

void loop() {
  // digitalRead and store pins of buttons
  int d10 = PINB & _BV(PINB2);
  int d11 = PINB & _BV(PINB3);
  int d12 = PINB & _BV(PINB4);

  if (!d10 && d12 && d11) {
    // Enable bit PORTD5
    PORTD |= _BV(PORTD5);
  }
  else
  {
    // Disable bit PORTD5
    PORTD &= ~_BV(PORTD5);
  }
  
  if (!d12 && d10 && d11) {
    PORTD |= _BV(PORTD6);
    Serial.print("Hello World!");
  }
  else
  {
    PORTD &= ~_BV(PORTD6);
  }
  if (!d10 && !d12 && d11) {
    // Timer for pin 3
    if ((TCCR2A & ~_BV(COM2B1))){
      TCCR2B &= 0b11111000 | 0x05;
      TCCR2A |= _BV(COM2B1) | _BV(COM2B0);
    }
    OCR2B = 128;
  } else {
    TCCR2A &= ~_BV(COM2B1);
    TCCR2A &= ~_BV(COM2B0);
  }
}
