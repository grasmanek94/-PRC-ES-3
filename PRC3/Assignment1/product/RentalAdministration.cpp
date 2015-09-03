#include <stdexcept>

#include "RentalAdministration.h"

Car* RentalAdministration::InternalFindCar(const std::string& licencePlate)//return std::shared_ptr<Car>!!!
{
	/*for (std::vector<Car*>::iterator it = _Cars.begin(); it != _Cars.end(); ++it)// or in C++11 and above: for(auto car_ptr: _Cars) { if(car_ptr->GetLicencePlate() ....
	{
		if (!(*it)->GetLicencePlate().compare(licencePlate))
		{
			return *it;
		}
	}*/
	for (size_t i = 0; i < _Cars.size(); ++i)
	{
		if (!_Cars[i]->GetLicencePlate().compare(licencePlate))
		{
			return _Cars[i];
		}
	}
	return NULL;//nullptr if decide to use raw pointers or std::shared_ptr<Car>()
}

std::vector<Car*> RentalAdministration::GetCars()//RAW :'(
{
	return _Cars;
}

Car* RentalAdministration::FindCar(const std::string& licencePlate)
{
	Car * car = InternalFindCar(licencePlate);
	if (!car)
	{
		throw std::out_of_range("licencePlate");
	}
	return car;
}

bool RentalAdministration::Add(Car* car)
{
	if (!car)
	{
		throw std::exception();
	}

	Car * fcar = InternalFindCar(car->GetLicencePlate());
	if (fcar)
	{
		return false;
	}

	_Cars.push_back(car);
	return true;
}

bool RentalAdministration::RentCar(const std::string& licencePlate)
{
	Car* car = FindCar(licencePlate);
	return car->Rent();
}

double RentalAdministration::ReturnCar(const std::string& licencePlate, int kilometers)
{
	Car* car = FindCar(licencePlate);
	return car->Return(kilometers);
}

void RentalAdministration::CleanCar(const std::string& licencePlate)
{
	Car* car = FindCar(licencePlate);
	car->Clean();
}