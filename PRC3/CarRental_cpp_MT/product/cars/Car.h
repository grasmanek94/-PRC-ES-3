#ifndef __CAR_H
#define __CAR_H

#include <string>
using namespace std;

class Car {
	public:
		Car(string manufacturer,
			string model,
			int buildYear,
			string licencePlate,
			double pricePerKm);
		virtual ~Car(void);
		int Rent();
		virtual double Return(int kilometers);
		virtual int NeedsCleaning() const = 0;
		virtual void Clean() = 0;
		string ToString() const;
		string GetManufacturer() const;
		string GetModel() const;
		int GetBuildYear() const;
		string GetLicencePlate() const;
		int GetKilometers() const;
		int IsAvailable() const;
		
	private:
		string manufacturer;
		string model;
		int buildYear;
		string licencePlate;
		int kilometers;
		int isAvailable;
		double pricePerKm;
};


#endif
