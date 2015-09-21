#include <string>
#include "Truck.h"

Truck::Truck(const std::string& model, const std::string& material, int diameter, int nrWheels, int power)
	: Car(model, material, diameter, nrWheels)
{
	this->power = new int;
	*(this->power) = power;
}
/* pre : diameter > 0, nrWheels > 2 and vermogen > 0
post: A Truck object is created that contains 'power' power and nrWheels
Wheel objects with the given material and diameter
*/

Truck::~Truck()
{
	delete power;
}
/* pre : -
post: the Truck object is destroyed including all allocated memory
*/

int Truck::getPower()
{
	return *power;
}
/* pre : -
post: returns power
*/

Truck::Truck(const Truck& myTruck)
	: Car(myTruck)
{
	this->power = new int;
	*(this->power) = *myTruck.power;
}
/* pre : -
post: a Truck object is created with all properties of myTruck, a deep copy is performed
*/

Truck& Truck::operator=(const Truck& myTruck)
{
	return *this;
}
/* pre : -
post: all properties of this object are replaced with myTruck's properties,
all previously existing properties are properly cleaned up and new
properties are deep copied
*/