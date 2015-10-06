#include <string>
#include <algorithm>
#include <stdexcept>

#include "Car.h"

Car::Car(const std::string& model, const std::string& material, int diameter, int nrWheels)
	: licencePlate(""), model(model)
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
	for (size_t i = 0; i < wheels.size(); ++i)
	{
		delete wheels[i];
		wheels[i] = NULL;
	}
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
	if (index < 0 || index >= getNrWheels())
	{
		throw std::out_of_range("illegal index");
	}

	return wheels[index];
}
/* pre : 0 <= index < nr wheels in <Car>
post: getWheel(i) = Wheel nr index of <Car>
*/

void Car::removeWheel(int index)
{
	if (index < 0 || index >= getNrWheels())
	{
		throw std::out_of_range("illegal index");
	}

	delete wheels[index];
	wheels[index] = NULL;

	wheels.erase(wheels.begin() + index);
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
	: licencePlate(myCar.licencePlate), model(myCar.model)
{
	for (size_t i = 0; i < myCar.wheels.size(); ++i)
	{
		wheels.push_back(new Wheel(*myCar.wheels[i]));
	}
}
/* pre : -
post: a Car object is created with all properties of myCar, a deep copy is performed
*/

Car& Car::operator=(const Car& mijnCar)
{
	Car temp(mijnCar);
	std::swap(licencePlate, temp.licencePlate);
	std::swap(model, temp.model);
	std::swap(wheels, temp.wheels);
	return *this;
}
/* pre : -
post: all properties of this object are replaced with myCar's properties,
all previously existing properties are properly cleaned up and new
properties are deep copied
*/