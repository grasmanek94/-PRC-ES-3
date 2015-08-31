#pragma once
#include <string>
#include <exception>

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
	std::string Manufacturer();
	std::string Model();
	int BuildYear();
	std::string LicencePlate();
	int Kilometers();
	bool IsAvailable();
};
