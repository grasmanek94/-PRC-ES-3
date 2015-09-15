#define SLIDER1  0

int hystVal = 2;
int sliderPrev = 0;

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

void setup() {
  
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
  TIMSK1 |= OCIE1A;

  // enable global interrupts
  sei();
}

void loop() {
  int sliderNow = analogRead(SLIDER1);

  if (sliderNow > sliderPrev + hystVal || sliderNow < sliderPrev - hystVal) {
    OCR1A = map(sliderNow, 0, 1023, 0, 0xFFFF);
    sliderPrev = sliderNow;    
  }
}
