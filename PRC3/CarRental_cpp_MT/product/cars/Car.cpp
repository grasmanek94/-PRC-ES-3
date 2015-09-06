#include <stdexcept>
using namespace std;

#include "Car.h"

Car::Car(	string manufacturer, string model, int buildYear,
			string licencePlate, double pricePerKm)
			: manufacturer(manufacturer)
			, model(model)
			, buildYear(buildYear)
			, licencePlate(licencePlate)
			, kilometers(0)
			, isAvailable(true)
			, pricePerKm(pricePerKm) {
	if (buildYear < 1890) {
		throw invalid_argument("Cars cannot be built before 1890.");
	}
	if (pricePerKm < 0) {
		throw invalid_argument("Price per km can't be negative.");
	}
}
	
int Car::Rent() {
	if (!isAvailable) {
		return false;
	}
	
	isAvailable = false;
	return true;
}

double Car::Return(int kilometers) {
	if (isAvailable) {
		throw invalid_argument("Car was not rented.");
	}
	if (kilometers < this->kilometers) {
		throw invalid_argument("Car returned with less kilometers\
								than rented");
	}
	double cost = pricePerKm * (kilometers - this->kilometers);
	this->kilometers = kilometers;
	isAvailable = true;
	return cost;
}

string Car::ToString() const {
	return 	manufacturer +
			" - " + model +
			", " + licencePlate;
}

string Car::GetManufacturer() const {
	return manufacturer;
}

string Car::GetModel() const {
	return model;
}

int Car::GetBuildYear() const {
	return buildYear;
}
	
string Car::GetLicencePlate() const {
	return licencePlate;
}

int Car::GetKilometers() const {
	return kilometers;
}

int Car::IsAvailable() const {
	return isAvailable;
}
