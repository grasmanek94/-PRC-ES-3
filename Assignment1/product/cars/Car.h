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
	virtual bool NeedsCleaning()  const;
	virtual void Clean();
	std::string ToString() const;
	std::string GetManufacturer() const;
	std::string GetModel() const;
	int GetBuildYear() const;
	std::string GetLicencePlate() const;
	int GetKilometers() const;
	bool IsAvailable() const;
};

#endif