#define SLIDER1  0

#define DATA     4
#define LED1     5
#define LED2     6
#define LATCH    7
#define CLOCK    8

int hystVal = 2;
int sliderPrev = 0;
boolean ledstate = false;

const uint8_t displayCharSet[] = 
{
  // each byte represent one appearance of the 8-segment display
  // each bit in a byte represent one segment of the 8-segment display
  0xC0, //  0
  0xF9, //  1
  0xA4, //  2
  0xB0, //  3
  0x99, //  4
  0x92, //  5
  0x82, //  6
  0xF8, //  7
  0x80, //  8
  0x90, //  9
  0x88, //  A
  0x83, //  b
  0xC6, //  C
  0xA1, //  d
  0x86, //  E
  0x8E  //  F
};

void inc_8segment(void)
{
  static int i = 0;
  uint8_t val;

  val = displayCharSet[i];

  digitalWrite(LATCH,LOW);
  shiftOut(DATA,CLOCK,MSBFIRST,val);  
  digitalWrite(LATCH,HIGH);

  i++;
  i %= sizeof (displayCharSet);
}

ISR(PCINT0_vect)
{
  ledstate = !ledstate;
  digitalWrite (LED1, ledstate);
}

ISR(TIMER1_COMPA_vect)
{
  inc_8segment();
}

void setup() {
  Serial.begin(9600);
  pinMode(11, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  
  // disable interrupts
  cli();

  // clear registers
  TCCR1A = 0;
  TCCR1B = 0;

  // CTC Mode
  TCCR1B |= _BV(WGM12);

  // Prescaler 64
  TCCR1B |= _BV(CS10) | _BV(CS11);

  // Timer interrupt enable
  TIMSK1 = 0;
  TIMSK1 |= _BV(OCIE1A);

  // Button interrupt
  PCMSK0 |= _BV (PCINT3); // This is D11
  PCIFR  |= _BV (PCIF0);
  PCICR  |= _BV (PCIE0); // Enable interrupt

  // enable global interrupts
  sei();
}

void loop() {
  int sliderNow = analogRead(SLIDER1);

  if (sliderNow > sliderPrev + hystVal || sliderNow < sliderPrev - hystVal) {
    sliderPrev = sliderNow;    
    cli();
    OCR1A = map(sliderNow, 0, 1023, 0, 65536);
    sei();
    Serial.println(sliderNow);
  }
}
