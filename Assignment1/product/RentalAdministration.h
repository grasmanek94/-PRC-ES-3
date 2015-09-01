#ifndef _RentalAdministration_H_
#define _RentalAdministration_H_

#include <string>
#include <map>
#include <exception>
#include <vector>

#include "cars/Car.h"

typedef std::map<std::string, Car*> CarsMap;

class RentalAdministration
{
	CarsMap _Cars;
	Car* GetCar(const std::string& licencePlate);
public:
	RentalAdministration();
	~RentalAdministration();
	bool Add(Car* car);
	bool RentCar(const std::string& licencePlate);
	double ReturnCar(const std::string& licensePlate, int kilometers);
	void CleanCar(const std::string& licencePlate);
	std::vector<Car*> GetCars();
};

#endif