#ifndef __SEDAN_H
#define __SEDAN_H

#include <string>
using namespace std;

#include "Car.h"

class Sedan: public Car {
	public:
		Sedan(string manufacturer,
			string model,
			int buildYear,
			string licensePlate,
			int hasTowbar);
		~Sedan(void);
		int HasTowBar() const;
		//double Return(int kilometers);
		int NeedsCleaning() const;
		void Clean();
		
		
	private:
		int lastCleanedAtKm;
		int hasTowbar;
};

#endif
