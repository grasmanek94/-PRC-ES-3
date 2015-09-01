#include "Car.h"

Car::Car(const std::string& manufacturer, const std::string& model,
	int buildYear, const std::string& licencePlate, double pricePerKm)
	: _Manufacturer(manufacturer), _Model(model), _BuildYear(buildYear),
	_LicencePlate(licencePlate), _Kilometers(0),_IsAvailable(true), _PricePerKm(pricePerKm)
{
	if (_BuildYear < 1890)
	{
		throw std::invalid_argument(""/*"cars cannot be built before 1890!"*/);
	}
	if (_PricePerKm < 0.0)
	{
		throw std::invalid_argument(""/*"PricePerKm cannot be smaller than 0"*/);
	}
}

Car::Car()
	: _Manufacturer(""), _Model(""), _BuildYear(1890),
	_LicencePlate(""), _Kilometers(0), _IsAvailable(true), _PricePerKm(999999999999.9999)
{
	if (_BuildYear < 1890)
	{
		throw std::invalid_argument(""/*"cars cannot be built before 1890!"*/);
	}
	if (_PricePerKm < 0.0)
	{
		throw std::invalid_argument(""/*"PricePerKm cannot be smaller than 0"*/);
	}
}

Car::~Car()
{

}

#ifndef TESTING
bool Car::Rent()
{
	if (!_IsAvailable)
	{
		return false;
	}

	_IsAvailable = false;
	return true;
}

double Car::Return(int kilometers)
{
	if (_IsAvailable)
	{
		throw std::logic_error(""/*"Car is not being rented"*/);
	}

	if (kilometers < _Kilometers)
	{
		throw std::invalid_argument(""/*"car is returned with less kilometers than it had"*/);
	}

	double cost = _PricePerKm * (double)(kilometers - _Kilometers);

	_Kilometers = kilometers;
	_IsAvailable = true;

	return cost;
}

std::string Car::GetLicencePlate()
{
	return _LicencePlate;
}

void Car::Clean()
{

}
#endif

std::string Car::ToString()
{
	return (GetManufacturer() + " - " + GetModel() + ", " + GetLicencePlate());
}

std::string Car::GetManufacturer()
{
	return _Manufacturer;
}

std::string Car::GetModel()
{
	return _Model;
}

int Car::GetBuildYear()
{
	return _BuildYear;
}

int Car::GetKilometers()
{
	return _Kilometers;
}

bool Car::IsAvailable()
{
	return _IsAvailable;
}

bool Car::NeedsCleaning()
{
	return false;
}