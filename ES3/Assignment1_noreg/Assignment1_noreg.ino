void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  pinMode(10, INPUT);//INPUT_PULLUP);
  pinMode(12, INPUT);//INPUT_PULLUP);
  
  
}

void loop() {
  int d10 = digitalRead(10);
  int d12 = digitalRead(12);

  if (d10) {
    digitalWrite(5, HIGH);
  }
  else
  {
    digitalWrite(5, LOW);
  }
  
  if (d12) {
    digitalWrite(6, HIGH);
    Serial.print("Hello World!");
  }
  else
  {
    digitalWrite(6, LOW);
  }
}

