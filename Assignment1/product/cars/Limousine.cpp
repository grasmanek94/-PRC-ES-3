#include "Limousine.h"

static const double pricePerKm = 2.50;

bool Limousine::HasMinibar() const
{
	return _HasMinibar;
}

bool Limousine::NeedsCleaning() const
{
	return _NeedsCleaning;
}

Limousine::Limousine(std::string manufacturer, std::string model, int buildYear, std::string licencePlate, bool hasMinibar)
	: Car(manufacturer, model, buildYear, licencePlate, pricePerKm)
{
	_HasMinibar = hasMinibar;
	_NeedsCleaning = false;
}

double Limousine::Return(int kilometers)
{
	double price = Car::Return(kilometers);
	_NeedsCleaning = true;
	return price;
}

void Limousine::Clean()
{
	_NeedsCleaning = false;
}