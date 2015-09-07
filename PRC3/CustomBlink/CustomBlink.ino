#include <StandardCplusplus.h>
#include <vector>

class Led
{
	int _Pin;
	long _TimeToPass;
	long _LastUpdateTime;
	bool _State;
public:
	Led(int pin, float hertz, bool initialState = false)
	{
		_LastUpdateTime = 0;
		_State = initialState;
		_Pin = pin;
		_TimeToPass = (long)(1000.0 / hertz);

		pinMode(_Pin, OUTPUT);
		digitalWrite(_Pin, _State);
	}

	void Update(long timeNow)
	{
		if (timeNow > (_LastUpdateTime + _TimeToPass))
		{
			_LastUpdateTime = timeNow;
			_State ^= 1;
			digitalWrite(_Pin, _State);
		}
	}

	long Elapsed(long timeNow) const
	{
		return (timeNow - _LastUpdateTime);
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
