#include "Sedan.h"

static const double PricePerKM = 0.29;

Sedan::Sedan(const std::string& manufacturer, const std::string& model,
	int buildYear, const std::string& licencePlate, bool hasTowBar)
	: Car(manufacturer, model, buildYear, licencePlate, PricePerKM)
{
	_LastCleanedAtKM = 0;
	_HasTowBar = hasTowBar;
}

Sedan::~Sedan()
{

}

void Sedan::Clean()
{
	_LastCleanedAtKM = GetKilometers();
}

bool Sedan::HasTowBar() const
{
	return _HasTowBar;
}

bool Sedan::NeedsCleaning() const
{
	return (GetKilometers() - _LastCleanedAtKM) >= 1000;
}