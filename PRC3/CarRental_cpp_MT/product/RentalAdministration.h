#ifndef __RENTALADMINISTRATION_H
#define __RENTALADMINISTRATION_H

#include <string>
#include <vector>
using namespace std;

#include "Car.h" //"cars/Car.h"

class RentalAdministration {
	public:
		RentalAdministration();
		int Add(Car* car);
		int RentCar(string licencePlate);
		double ReturnCar(string licencePlate, int kilometers);
		void CleanCar(string licencePlate);
		vector<Car*> GetCars() const;
		
		
	private:
		Car* findCar(string licencePlate);
		Car* findCarWithException(string licencePlate);
		vector<Car*> cars;
};

#endif
