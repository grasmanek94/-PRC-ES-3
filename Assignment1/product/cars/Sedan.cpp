#include "Sedan.h"

static const double PricePerKM = 0.29;

Sedan::Sedan(const std::string& manufacturer, const std::string& model,
	int buildYear, const std::string& licencePlate, bool hasTowBar)
	: _HasTowBar(hasTowBar), Car(manufacturer, model, buildYear, licencePlate, PricePerKM), _LastCleanedAtKM(0)
{

}

Sedan::~Sedan()
{

}

void Sedan::Clean()
{
	_LastCleanedAtKM = Kilometers();
}

bool Sedan::HasTowBar()
{
	return _HasTowBar;
}

bool Sedan::NeedsCleaning()
{
	return (Kilometers() - _LastCleanedAtKM) >= 1000;
}