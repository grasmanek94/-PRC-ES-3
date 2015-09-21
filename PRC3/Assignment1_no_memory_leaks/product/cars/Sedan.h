#ifndef __SEDAN_H
#define __SEDAN_H

#include "Car.h"

class Sedan : public Car
{
private:
	int _LastCleanedAtKm;
	bool _HasTowbar;
public:
	bool HasTowBar() const;
	bool NeedsCleaning() const;
	Sedan(std::string manufacturer, std::string model, int buildYear, std::string licencePlate, bool hasTowbar);
	void Clean();
};

#endif