#include <StandardCplusplus.h>
#include <vector>
/*
uint8_t analog_reference = DEFAULT;

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~(1 << bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= (1 << bit))

const uint8_t digital_pin_to_port[] = {
	4, // 0 
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	2, // 8 
	2,
	2,
	2,
	2,
	2,
	3, // 14 
	3,
	3,
	3,
	3,
	3,
};

const uint8_t digital_pin_to_bit_mask[] = {
	1 << 0, // 0, port D 
	1 << 1,
	1 << 2,
	1 << 3,
	1 << 4,
	1 << 5,
	1 << 6,
	1 << 7,
	1 << 0, // 8, port B 
	1 << 1,
	1 << 2,
	1 << 3,
	1 << 4,
	1 << 5,
	1 << 0, // 14, port C 
	1 << 1,
	1 << 2,
	1 << 3,
	1 << 4,
	1 << 5,
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, // 0 - port D 
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER2B,
	NOT_ON_TIMER,
	TIMER0B,
	TIMER0A,
	NOT_ON_TIMER,
	NOT_ON_TIMER, // 8 - port B 
	TIMER1A,
	TIMER1B,
	TIMER2A,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, // 14 - port C
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
};

const uint16_t port_to_mode[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t)&DDRB,
	(uint16_t)&DDRC,
	(uint16_t)&DDRD,
};

const uint16_t port_to_output[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t)&PORTB,
	(uint16_t)&PORTC,
	(uint16_t)&PORTD,
};

const uint16_t port_to_input[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t)&PINB,
	(uint16_t)&PINC,
	(uint16_t)&PIND,
};

#define digitalPinToBitMask(P) digital_pin_to_bit_mask[P]
#define digitalPinToPort(P) digital_pin_to_port[P]
#define digitalPinToTimer(P) digital_pin_to_timer[P]
#define analogInPinToBit(P) (P)
#define portOutputRegister(P) ((volatile uint8_t *)port_to_output[P])
#define portInputRegister(P) ((volatile uint8_t *)port_to_input[P])
#define portModeRegister(P) ((volatile uint8_t *)port_to_mode[P])

void _pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *reg, *out;

	if (port == NOT_A_PIN) return;

	reg = portModeRegister(port);
	out = portOutputRegister(port);

	if (mode == INPUT) {
		uint8_t oldSREG = SREG;
		cli();
		*reg &= ~bit;
		*out &= ~bit;
		SREG = oldSREG;
	}
	else if (mode == INPUT_PULLUP) {
		uint8_t oldSREG = SREG;
		cli();
		*reg &= ~bit;
		*out |= bit;
		SREG = oldSREG;
	}
	else {
		uint8_t oldSREG = SREG;
		cli();
		*reg |= bit;
		SREG = oldSREG;
	}
}

static void turnOffPWM(uint8_t timer)
{
	switch (timer)
	{
		case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
		case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
		case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
		case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
		case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
		case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
	}
}

void _digitalWrite(uint8_t pin, uint8_t val)
{
	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *out;

	if (port == NOT_A_PIN) return;

	// If the pin that support PWM output, we need to turn it off
	// before doing a digital write.
	if (timer != NOT_ON_TIMER) turnOffPWM(timer);

	out = portOutputRegister(port);

	uint8_t oldSREG = SREG;
	cli();

	if (val == LOW) {
		*out &= ~bit;
	}
	else {
		*out |= bit;
	}

	SREG = oldSREG;
}

int _digitalRead(uint8_t pin)
{
	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);

	if (port == NOT_A_PIN) return LOW;

	// If the pin that support PWM output, we need to turn it off
	// before getting a digital reading.
	if (timer != NOT_ON_TIMER) turnOffPWM(timer);

	if (*portInputRegister(port) & bit) return HIGH;
	return LOW;
}

int _analogRead(uint8_t pin)
{
	uint8_t low, high;

	if (pin >= 14) pin -= 14; // allow for channel or pin numbers

	ADMUX = (analog_reference << 6) | (pin & 0x07);

	// start the conversion
	sbi(ADCSRA, ADSC);

	// ADSC is cleared when the conversion finishes
	while (bit_is_set(ADCSRA, ADSC));

	// we have to read ADCL first; doing so locks both ADCL
	// and ADCH until ADCH is read.  reading ADCL second would
	// cause the results of each conversion to be discarded,
	// as ADCL and ADCH would be locked when it completed.
	low  = ADCL;
	high = ADCH;

	// combine the two bytes
	return (high << 8) | low;
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
void _analogWrite(uint8_t pin, int val)
{
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.
	pinMode(pin, OUTPUT);
	if (val == 0)
	{
		digitalWrite(pin, LOW);
	}
	else if (val == 255)
	{
		digitalWrite(pin, HIGH);
	}
	else
	{
		switch(digitalPinToTimer(pin))
		{
			case TIMER0A:
				// connect pwm to pin on timer 0, channel A
				sbi(TCCR0A, COM0A1);
				OCR0A = val; // set pwm duty
				break;
	
			case TIMER0B:
				// connect pwm to pin on timer 0, channel B
				sbi(TCCR0A, COM0B1);
				OCR0B = val; // set pwm duty
				break;
	
			case TIMER1A:
				// connect pwm to pin on timer 1, channel A
				sbi(TCCR1A, COM1A1);
				OCR1A = val; // set pwm duty
				break;

			case TIMER1B:
				// connect pwm to pin on timer 1, channel B
				sbi(TCCR1A, COM1B1);
				OCR1B = val; // set pwm duty
				break;
	
			case TIMER2A:
				// connect pwm to pin on timer 2, channel A
				sbi(TCCR2A, COM2A1);
				OCR2A = val; // set pwm duty
				break;
	
			case TIMER2B:
				// connect pwm to pin on timer 2, channel B
				sbi(TCCR2A, COM2B1);
				OCR2B = val; // set pwm duty
				break;

			case NOT_ON_TIMER:
			default:
				if (val < 128) {
					digitalWrite(pin, LOW);
				} else {
					digitalWrite(pin, HIGH);
				}
		}
	}
}*/

class Timer
{
	long _TimeToPass;
	long _LastUpdateTime;
public:
	Timer(float hertz)
	{
		_LastUpdateTime = 0;
		_TimeToPass = (long)(1000.0 / hertz);
	}

	bool Tick(long timeNow)
	{
		if (timeNow > (_LastUpdateTime + _TimeToPass))
		{
			_LastUpdateTime = timeNow;
			return true;
		}
		return false;
	}

	long Elapsed(long timeNow) const
	{
		return (timeNow - _LastUpdateTime);
	}
};

class Led
{
	int _Pin;
	bool _State;
	Timer _Timer;
public:
	Led(int pin, float hertz, bool initialState = false)
		: _Timer(hertz)
	{
		_State = initialState;
		_Pin = pin;

		pinMode(_Pin, OUTPUT);
		digitalWrite(_Pin, _State);
	}

	void Update(long timeNow)
	{
		if (_Timer.Tick(timeNow))
		{
			_State ^= 1;
			digitalWrite(_Pin, _State);
		}
	}

	int Pin() const
	{
		return _Pin;
	}
};

class LedManager
{
	std::vector<Led> Leds;
public:
	LedManager() {}

	bool Add(const Led& led)
	{
		for (auto& i : Leds)
		{
			if (i.Pin() == led.Pin())
			{
				return false;
			}
		}

		Leds.push_back(led);
		return true;
	}

	bool Remove(int pin)
	{
		for (auto i = Leds.begin(); i != Leds.end(); ++i)
		{
			if (i->Pin() == pin)
			{
				Leds.erase(i);
				return true;
			}
		}

		return false;
	}
	void Update()
	{
		long timeNow = millis();
		for (auto& i : Leds)
		{
			i.Update(timeNow);
		}
	}
};

LedManager manager;

void setup()
{
	manager.Add(Led(11, 2.0));
	manager.Add(Led(12, 4.0));
	manager.Add(Led(13, 8.0));
}

void loop()
{
	manager.Update();
}
