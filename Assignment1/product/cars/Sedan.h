#ifndef _Sedan_H_
#define _Sedan_H_

#include <string>
#include "Car.h"

class Sedan :
	public Car
{
	bool _HasTowBar;
	int _LastCleanedAtKM;
public:
	Sedan(const std::string& manufacturer, const std::string& model,
		int buildYear, const std::string& licencePlate, bool hasTowBar);
	~Sedan();
	void Clean();
	bool HasTowBar();
	bool NeedsCleaning();
};

#endif