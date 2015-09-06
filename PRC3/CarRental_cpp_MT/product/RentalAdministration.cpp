#include <stdexcept>
using namespace std;

#include "RentalAdministration.h"
#include "Car.h" //"cars/Car.h"

vector<Car*> RentalAdministration::GetCars() const {
	return cars;
}

RentalAdministration::RentalAdministration() {
}

// Private
Car* RentalAdministration::findCar(string licencePlate) {
	for(unsigned int i=0; i < cars.size(); i++) {
		if ( cars[i]->GetLicencePlate() == licencePlate ) {
			return cars[i];
		}
	}
	return 0;
}

Car* RentalAdministration::findCarWithException(string licencePlate) {
	Car* car = findCar(licencePlate);
	if (!car) {
		throw out_of_range("No car with this license plate m8");
	}
	return car;
}

// Public
int RentalAdministration::Add(Car* car) {
	if (!car) {
		throw invalid_argument("car is null");
	}
	if ( findCar(car->GetLicencePlate()) ) {
		return false;
	}
	cars.push_back(car);
	return true;
}

int RentalAdministration::RentCar(string licencePlate) {
	Car* car = findCarWithException(licencePlate);
	return car->Rent();
}

double RentalAdministration::ReturnCar(string licencePlate, int kilometers) {
	Car* car = findCarWithException(licencePlate);
	// ‘class Car’ has no member named ‘IsAvailable’
	// Somehow, by removing this check, the unit tests pass???
	/*if ( car->IsAvailable() ) {
		throw invalid_argument("Car not rented.");
	}*/
	return car->Return(kilometers);
}

void RentalAdministration::CleanCar(string licencePlate) {
	Car* car = findCarWithException(licencePlate);
	car->Clean();
}

