#include <string>

#include "Car.h"

Car::Car(const std::string& model, const std::string& material, int diameter, int nrWheels)
	: model(model)
{
	if (!(nrWheels > 2) || !(diameter > 0))
	{
		throw std::invalid_argument("");
	}

	for (int i = 0; i < nrWheels; ++i)
	{
		wheels.push_back(new Wheel(diameter, material));
	}
}
/* pre : diameter > 0 and nrWheels > 2
post: A Car object is created that contains nrWheels Wheel objects
with the given material and diameter
*/

Car::~Car()
{

}
/* pre : -
post: the Car object is destroyed including all allocated memory
*/

std::string Car::getModel()
{
	return model;
}
/* pre : -
post: getModel()= <Car> model
*/

void Car::setLicencePlate(const std::string& licence)
{
	licencePlate = licence;
}
/* pre : -
post: <Car>'s licence plate is licence
*/

std::string Car::getLicencePlate()
{
	return licencePlate;
}
/* pre : -
post: getLicencePlate()= <Car>'s licence plate
*/

int Car::getNrWheels()
{
	return wheels.size();
}
/* pre : -
post: getNrWheels()= <Car>'s nr wheels
*/

Wheel* Car::getWheel(int index)
{
	return wheels[index];
}
/* pre : 0 <= index < nr wheels in <Car>
post: getWheel(i) = Wheel nr index of <Car>
*/

void Car::removeWheel(int index)
{
	delete wheels[index];
	wheels[index] = NULL;
}
/* pre : -
post: if 0 <= index < nr wheels in <Car>
then wheel nr index is removed from <Car>
else out_of_range exception with text: "illegal index" is thrown
*/

void Car::addWheel(int diameter, const std::string& material)
{
	wheels.push_back(new Wheel(diameter, material));
}
/* pre : diameter > 0
post: a wheel with given diameter and material is added to <Car>
*/

Car::Car(const Car& myCar)
{

}
/* pre : -
post: a Car object is created with all properties of myCar, a deep copy is performed
*/

Car& Car::operator=(const Car& mijnCar)
{
	return *this;
}
/* pre : -
post: all properties of this object are replaced with myCar's properties,
all previously existing properties are properly cleaned up and new
properties are deep copied
*/