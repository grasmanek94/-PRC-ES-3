#pragma once
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
	void Clean() override;
	double Return(int kilometers) override;
	bool HasMiniBar();
	bool NeedsCleaning() override;
};

