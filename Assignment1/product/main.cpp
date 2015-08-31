#include <iostream>
#include <string>

#include "cars/Car.h"
#include "cars/Sedan.h"
#include "cars/Limousine.h"
#include "RentalAdministration.h"

RentalAdministration admin;

int main()
{
	std::cout << admin.Add(Sedan("Volvo", "S40", 1999, "111111", true));
	std::cout << admin.Add(Sedan("Audi", "A4", 2000, "222222", true));
	std::cout << admin.Add(Limousine("Unk", "Unk", 2010, "333333", true));
	std::cout << admin.Add(Limousine("Unk", "Unk", 2010, "333333", true));

	std::cout << std::endl;

	std::cout << admin.RentCar("222222");
	std::cout << admin.RentCar("222222");

	std::cout << std::endl;

	std::cout << admin.ReturnCar("222222", 500);

	while (true);
	return 0;
}