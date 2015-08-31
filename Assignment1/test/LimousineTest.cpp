#include <string>
#include <stdexcept>
#include "gtest/gtest.h"
using namespace std;

#include "Limousine.h"

static const double LimousinePricePerKm = 2.5;

static void CheckLimousineProperties(Limousine* limousinePtr, string manufacturer, string model, int buildYear,
                                     string licencePlate, int kilometers, bool isAvailable, bool hasMinibar)
{
    EXPECT_EQ(manufacturer, limousinePtr->GetManufacturer());
    EXPECT_EQ(model, limousinePtr->GetModel());
    EXPECT_EQ(buildYear, limousinePtr->GetBuildYear());
    EXPECT_EQ(licencePlate, limousinePtr->GetLicencePlate());
    EXPECT_EQ(kilometers, limousinePtr->GetKilometers());
    EXPECT_EQ(isAvailable, limousinePtr->IsAvailable());
    EXPECT_EQ(hasMinibar, limousinePtr->HasMinibar());
}

class LimousineTest : public ::testing::Test
{
    protected:
        LimousineTest()
        {
            testPtr = new Limousine("Mercedes-Maybach", "S-Klasse", 2014, "2-c++-11", true);
        }
        
        Limousine* testPtr;
};

TEST_F(LimousineTest, test_construction_values_copied_correctly)
{
    CheckLimousineProperties(testPtr, "Mercedes-Maybach", "S-Klasse", 2014, "2-c++-11", 0, true, true);
}

TEST_F(LimousineTest, test_car_needsCleaning_after_construction)
{
    EXPECT_FALSE(testPtr->NeedsCleaning());
}

TEST_F(LimousineTest, test_car_needsCleaning)
{
    EXPECT_TRUE(testPtr->Rent());
    EXPECT_FALSE(testPtr->NeedsCleaning());
    EXPECT_EQ(LimousinePricePerKm * 1, testPtr->Return(1));
    EXPECT_TRUE(testPtr->NeedsCleaning());
}
