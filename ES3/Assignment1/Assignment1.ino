/*
   Pins:  10    Port:  B2
          12           B4
          5            D5
          6            D6
          
*/

void setup() {
  Serial.begin(9600);
  
  DDRB |= _BV(2) | _BV(4);
  
  //pinMode(5, OUTPUT);
  //pinMode(6, OUTPUT);
  
  DDRD &= !(_BV(5) | _BV(6));
  PORTD |= _BV(5) | _BV(6);
  //pinMode(10, INPUT_PULLUP);
  //pinMode(12, INPUT_PULLUP);
  
  
}

void loop() {
  int d10 = digitalRead(10);
  int d12 = digitalRead(12);

  if (!d10) {
    digitalWrite(5, HIGH);
  }
  else
  {
    digitalWrite(5, LOW);
  }
  
  if (!d12) {
    digitalWrite(6, HIGH);
    Serial.print("Hello World!");
    delay(1000);
  }
  else
  {
    digitalWrite(6, LOW);
  }
  if (!d10 && !d12) {
    // tone();
  }
}

