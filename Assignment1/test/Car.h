#ifndef __CAR_H
#define __CAR_H

#include "gmock/gmock.h"

#include <string>
using namespace std;

class Car
{
	//std::string _Manufacturer;
	//std::string _Model;
	//int _BuildYear;
	//std::string _LicencePlate;
	//int _Kilometers;
	//bool _IsAvailable;
	//double _PricePerKm;
public:
	//Car(const std::string& manufacturer, const std::string& model,
	//	int buildYear, const std::string& licencePlate, double pricePerKm);
	//Car();
	//~Car();
	//
	//virtual bool NeedsCleaning();
	//std::string ToString();
	//std::string GetManufacturer();
	//std::string GetModel();
	//int GetBuildYear();
	//int GetKilometers();
	//bool IsAvailable();

    MOCK_CONST_METHOD0(GetLicencePlate, string());
    MOCK_METHOD0(Rent, bool());
    MOCK_METHOD1(Return, double(int kilometers));
    MOCK_METHOD0(Clean, void());
};


#endif