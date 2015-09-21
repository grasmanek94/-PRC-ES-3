#ifndef __LIMOUSINE_H
#define __LIMOUSINE_H

#include "Car.h"

class Limousine : public Car
{
private:
	bool _NeedsCleaning;
	bool _HasMinibar;
public:
	bool HasMinibar() const;
	bool NeedsCleaning() const;
	Limousine(std::string manufacturer, std::string model, int buildYear, std::string licencePlate, bool hasMinibar);
	double Return(int kilometers);
	void Clean();
};

#endif