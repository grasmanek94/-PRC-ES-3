#ifndef __RENTALADMINISTRATION_H
#define __RENTALADMINISTRATION_H

#include <vector>

#include "Car.h"

class RentalAdministration
{
private:
	std::vector<Car*> _Cars;// std::map zou zoveel beter zijn, std::map<std::string, std::shared_ptr<Car>>

	Car* InternalFindCar(const std::string& licencePlate);
public:
	std::vector<Car*> GetCars();
	Car* FindCar(const std::string& licencePlate);
	bool Add(Car* car);
	bool RentCar(const std::string& licencePlate);
	double ReturnCar(const std::string& licencePlate, int kilometers);
	void CleanCar(const std::string& licencePlate);
	~RentalAdministration();
};

#endif