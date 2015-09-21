#include <stdexcept>
using namespace std;

#include "Car.h"
#include "Limousine.h"

static const double PricePerKm = 2.5;
			
int Limousine::HasMinibar() const {
	return hasMinibar;
}

int Limousine::NeedsCleaning() const {
	return needsCleaning;
}

Limousine::Limousine(string manufacturer, string model, int buildYear, 
			string licencePlate, int hasMinibar)
			: Car(manufacturer
			, model
			, buildYear
			, licencePlate
			, PricePerKm) {
	this->hasMinibar = hasMinibar;
	needsCleaning = false;
}

Limousine::~Limousine(void) {
}

double Limousine::Return(int kilometers) {
	double price = Car::Return(kilometers);
	needsCleaning = true;
	return price;
}

void Limousine::Clean() {
	needsCleaning = false;
}

