#include <stdexcept>

#include "Car.h"

std::string Car::GetLicencePlate() const
{
	return _LicencePlate;
}
std::string Car::GetManufacturer() const
{
	return _Manufacturer;
}
std::string Car::GetModel() const
{
	return _Model;
}
int Car::GetBuildYear() const
{
	return _BuildYear;
}
int Car::GetKilometers() const
{
	return _Kilometers;
}
bool Car::IsAvailable() const
{
	return _IsAvailable;
}

void Car::Clean()
{

}

Car::Car(std::string manufacturer, std::string model, int buildYear, std::string licencePlate, double pricePerKm)
{
	if (buildYear < 1890)
	{
		throw std::invalid_argument("");
	}
	if (pricePerKm < 0)
	{
		throw std::invalid_argument("");
	}

	_Manufacturer = manufacturer;
	_Model = model;
	_BuildYear = buildYear;
	_LicencePlate = licencePlate;
	_Kilometers = 0;
	_IsAvailable = true;
	_PricePerKm = pricePerKm;
}

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
		throw std::logic_error("car was not rented");
	}
	if (kilometers < _Kilometers)
	{
		throw std::invalid_argument("car is returned with less kilometers than it had");
	}

	double cost = _PricePerKm * (kilometers - _Kilometers);
	_Kilometers = kilometers;
	_IsAvailable = true;
	return cost;
}

std::string Car::ToString() const
{
	return _Manufacturer +
		" - " + _Model +
		", " + _LicencePlate;
}

bool Car::NeedsCleaning() const
{
	return false;
}