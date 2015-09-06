/*
   Pins:  10    Port:  B2  Button
          12           B4  Button
          5            D5  LED
          6            D6  LED
          3            D3  Buzzer
          
   Buttons: 10 & 12
   LEDs   : 5  & 6
   Buzzer : 3
*/

//Buzzer help thing
bool toot = true;

void setup() {
  Serial.begin(9600);
  
  // Simultaneously set DDD5 and DDD6 as output
  // Also DDD3
  DDRD |= _BV(DDD5) | _BV(DDD6) | _BV(DDD3);
  
  // Set DDB2 and DDB4 as input
  DDRB  &= ~(_BV(DDB2) | _BV(DDB4));
  
  // Pullup bits
  //PORTB |=   _BV(PORTB2) | _BV(PORTB4);  
}

void loop() {
  // Read and store pins d10 & d12
  int d10 = PINB & _BV(PINB2);
  int d12 = PINB & _BV(PINB4);

  if (d10) {
    // Enable bit PORTD5
    PORTD |= _BV(PORTD5);
  }
  else
  {
    // Disable bit PORTD5
    PORTD &= ~_BV(PORTD5);
  }
  
  if (d12) {
    PORTD |= _BV(PORTD6);
    Serial.print("Hello World!");
  }
  else
  {
    PORTD &= ~_BV(PORTD6);
  }
  if (d10 && d12) {
    if (toot) {
      PORTD &= ~_BV(PORTD3);
    }
    else {
      PORTD |= _BV(PORTD3);
    }
    toot = !toot;
    //Serial.print stealing precious microseconds
    //Also I don't know how to make non-blocking sounds
    //in combination with port manipulation manually
    //delayMicroseconds(500);
  }
}

