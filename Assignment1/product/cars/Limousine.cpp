#include "Limousine.h"

static const double PricePerKM = 2.5;

Limousine::Limousine(const std::string& manufacturer, const std::string& model,
	int buildYear, const std::string& licencePlate, bool hasMiniBar)
	: _HasMiniBar(hasMiniBar), Car(manufacturer, model, buildYear, licencePlate, PricePerKM), _NeedsCleaning(false)
{

}

Limousine::~Limousine()
{

}

void Limousine::Clean()
{
	_NeedsCleaning = false;
}

bool Limousine::NeedsCleaning()
{
	return _NeedsCleaning;
}

bool Limousine::HasMiniBar()
{
	return _HasMiniBar;
}

double Limousine::Return(int kilometers)
{
	double cost = Car::Return(kilometers);

	_NeedsCleaning = true;

	return cost;
}