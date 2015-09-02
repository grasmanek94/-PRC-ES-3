#ifndef _Limousine_H_
#define _Limousine_H_

#include <string>
#include "Car.h"

class Limousine :
	public Car
{
	bool _HasMiniBar;
	bool _NeedsCleaning;
public:
	Limousine(const std::string& manufacturer, const std::string& model,
		int buildYear, const std::string& licencePlate, bool hasMiniBar);
	~Limousine();
	void Clean();
	double Return(int kilometers);
	bool HasMinibar() const;
	bool NeedsCleaning() const;
};

#endif