#include "RentalAdministration.h"

RentalAdministration::RentalAdministration()
{

}

RentalAdministration::~RentalAdministration()
{

}

bool RentalAdministration::Add(Car& car)
{
	try
	{
		Car& unused = GetCar(car.LicencePlate());
		return false;
	}
	catch (const std::exception&)
	{
		_Cars[car.LicencePlate()] = car;
		return true;
	}
}

bool RentalAdministration::RentCar(const std::string& licencePlate)
{
	Car& car = GetCar(licencePlate);
	return car.IsAvailable() && car.Rent();
}

double RentalAdministration::ReturnCar(const std::string& licencePlate, int kilometers)
{
	Car& car = GetCar(licencePlate);
	return car.Return(kilometers);
}

Car& RentalAdministration::GetCar(const std::string& licencePlate)
{
	CarsMap::iterator it = _Cars.find(licencePlate);
	if (_Cars.end() == it)
	{
		throw std::exception("Car with such licence plate does not exist");
	}
	return it->second;
}