#ifndef __LIMOUSINE_H
#define __LIMOUSINE_H

#include <string>
using namespace std;

#include "Car.h"

class Limousine: public Car {
	public:
		Limousine(string manufacturer,
			string model,
			int buildYear,
			string licencePlate,
			int hasMinibar);
		int HasMinibar() const;
		double Return(int kilometers);
		int NeedsCleaning() const;
		void Clean();
		~Limousine(void);
	private:
		int hasMinibar;
		int needsCleaning;
		
};

#endif
