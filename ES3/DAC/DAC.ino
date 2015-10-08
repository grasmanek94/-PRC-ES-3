#define pot A0

uint8_t toneMap[360];
int prevPot = 0;
int iteration = 0;
int hyst = 2;

// Happens when timer register hits OCR1A
ISR(TIMER1_COMPA_vect) {
  cli();
  // Simply set the tone map
  PORTD = toneMap[iteration];
  sei();

  // Loop through all tonemaps
  iteration++;
  if (iteration == sizeof(toneMap)) {
    iteration = 0;
  }
  //Serial.println(mask);
}

void generateSinus() {
  for (int x = 0; x < 360; x++) {
    // Generate -1 to 1
    float sine = sin(((float)x/360.0) * 2.0 * M_PI);

    // Map -1, 1 to 0, 255;
    toneMap[x] = (int)((sine+1.0)*127);
    Serial.println(toneMap[x]);
  }
}


void setup() {
  Serial.begin(9600);
  generateSinus();

  cli();

  // Clear Timer/Counter Control registers
  TCCR1A = 0;
  TCCR1B = 0;
  
  // CTC mode
  TCCR1B |= _BV(WGM12);

  // Prescaler: 1
  TCCR1B |= _BV(CS10);

  // Clear timer interrupt register
  TIMSK1 = 0;
  
  // Output Compare Interrupt Enable 1 A
  TIMSK1 |= _BV(OCIE1A);

  // Port D has the pins we want
  DDRD = 0;
  DDRD |= _BV(DDD2) | _BV(DDD3) | _BV(DDD4) | _BV(DDD5) | _BV(DDD6) | _BV(DDD7);
  
  sei();
}


/* Change compare interval if a change in
 * the potmeter has been detected. Also apply
 * some hysterisis to get a more stable reading.
 * Changing the potmeter changes the delay in between
 * each toneMap being written, so effectively the
 * period of the sine wave is changed.
 */

void loop() {
  int currPot = analogRead(pot);
  if (currPot > prevPot + hyst || currPot < prevPot - hyst) {
    prevPot = currPot;
    cli();
    OCR1A = map(currPot, 0, 1023, 0, 65535);
    sei();
  }
}

