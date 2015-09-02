#ifndef __CAR_H
#define __CAR_H

#include "gmock/gmock.h"

#include <string>
using namespace std;

class Car
{
    public:
        MOCK_CONST_METHOD0(GetLicencePlate, string());
        MOCK_METHOD0(Rent, bool());
        MOCK_METHOD1(Return, double(int kilometers));
        MOCK_METHOD0(Clean, void());
};


#endif