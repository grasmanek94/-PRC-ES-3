#include <stdexcept>
using namespace std;

#include "Car.h"
#include "Sedan.h"

static const double PricePerKm = 0.29;

Sedan::Sedan(string manufacturer, string model, int buildYear,
			string licencePlate, int hasTowbar)
			: Car(manufacturer
			, model
			, buildYear
			, licencePlate
			, PricePerKm) {
	this->hasTowbar = hasTowbar;
	lastCleanedAtKm = 0;
}

Sedan::~Sedan(void){
}

int Sedan::HasTowBar() const {
	return hasTowbar;
}

int Sedan::NeedsCleaning() const {
	return (GetKilometers() - lastCleanedAtKm) >= 1000;
}

void Sedan::Clean() {
	lastCleanedAtKm = GetKilometers();
}
