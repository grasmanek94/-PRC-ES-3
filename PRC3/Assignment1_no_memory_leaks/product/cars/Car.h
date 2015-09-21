#ifndef __CAR_H
#define __CAR_H

#include <string>

class Car
{
private:
	double _PricePerKm;
	std::string _Manufacturer;
	std::string _Model;
	std::string _LicencePlate;
	int _BuildYear;
	int _Kilometers;
	bool _IsAvailable;
public:
	std::string GetLicencePlate() const;
	std::string GetManufacturer() const;
	std::string GetModel() const;
	int GetBuildYear() const;
	int GetKilometers() const;
	bool IsAvailable() const;
	Car(std::string manufacturer, std::string model, int buildYear, std::string licencePlate, double pricePerKm);
	bool Rent();
	double Return(int kilometers);
	std::string ToString() const;
	virtual bool NeedsCleaning() const = 0;
	virtual void Clean() = 0;
	virtual ~Car();
};

#endif