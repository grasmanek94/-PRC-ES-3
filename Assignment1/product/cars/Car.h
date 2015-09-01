#ifndef _Car_H_
#define _Car_H_

#include <string>
#include <exception>
#include <stdexcept>

class Car
{
	std::string _Manufacturer;
	std::string _Model;
	int _BuildYear;
	std::string _LicencePlate;
	int _Kilometers;
	bool _IsAvailable;
	double _PricePerKm;
public:
	Car(const std::string& manufacturer, const std::string& model,
		int buildYear, const std::string& licencePlate, double pricePerKm);
	Car();
	~Car();

	bool Rent();
	virtual double Return(int kilometers);
	virtual bool NeedsCleaning();
	virtual void Clean();
	std::string ToString();
	std::string GetManufacturer();
	std::string GetModel();
	int GetBuildYear();
	std::string GetLicencePlate();
	int GetKilometers();
	bool IsAvailable();
};

#endif