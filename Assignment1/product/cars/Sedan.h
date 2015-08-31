#pragma once
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
	void Clean() override;
	bool HasTowBar();
	bool NeedsCleaning() override;
};

