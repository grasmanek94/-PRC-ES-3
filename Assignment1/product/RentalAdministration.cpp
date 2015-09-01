#include "RentalAdministration.h"

RentalAdministration::RentalAdministration()
{

}

RentalAdministration::~RentalAdministration()
{

}

bool RentalAdministration::Add(Car* car)
{
	try
	{
		GetCar(car->GetLicencePlate());
		return false;
	}
	catch (std::exception)
	{
		_Cars[car->GetLicencePlate()] = new Car(*car);
		return true;
	}
}

bool RentalAdministration::RentCar(const std::string& licencePlate)
{
	Car* car = GetCar(licencePlate);
	return car->IsAvailable() && car->Rent();
}

double RentalAdministration::ReturnCar(const std::string& licencePlate, int kilometers)
{
	return GetCar(licencePlate)->Return(kilometers);
}

Car* RentalAdministration::GetCar(const std::string& licencePlate)
{
	CarsMap::iterator it = _Cars.find(licencePlate);
	if (_Cars.end() == it)
	{
		throw std::exception(/*"Car with such licence plate does not exist"*/);
	}
	return it->second;
}

void RentalAdministration::CleanCar(const std::string& licencePlate)
{
	GetCar(licencePlate)->Clean();
}

template <typename M, typename V>
void MapToVec(const  M & m, V & v) {
	for (typename M::const_iterator it = m.begin(); it != m.end(); ++it) {
		v.push_back(it->second);
	}
}

std::vector<Car*> RentalAdministration::GetCars()
{
	std::vector<Car*> cars;
	MapToVec(_Cars, cars);
	return cars;
}