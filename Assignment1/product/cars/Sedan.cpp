#include "Sedan.h"

static const double pricePerKm = 0.29;

bool Sedan::HasTowBar() const
{
	return _HasTowbar;
}

bool Sedan::NeedsCleaning() const
{
	return (GetKilometers() - _LastCleanedAtKm) >= 1000;
}

Sedan::Sedan(std::string manufacturer, std::string model, int buildYear, std::string licencePlate, bool hasTowbar)
	: Car(manufacturer, model, buildYear, licencePlate, pricePerKm)
{
	_HasTowbar = hasTowbar;
	_LastCleanedAtKm = 0;
}

void Sedan::Clean()
{
	_LastCleanedAtKm = GetKilometers();
}