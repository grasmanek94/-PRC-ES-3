#include <string>
#include <stdexcept>
#include "gtest/gtest.h"

#include "Truck.h"

static void CheckTruckProperties(Truck* ptr, std::string model, std::string licencePlate, int wheels, int power)
{
	EXPECT_EQ(model, ptr->getModel());
	EXPECT_EQ(licencePlate, ptr->getLicencePlate());
	EXPECT_EQ(wheels, ptr->getNrWheels());
	EXPECT_EQ(power, ptr->getPower());
}

TEST(TruckIllegalParameterTests, test_construction_exception)
{
	EXPECT_THROW(new Truck("Audi", "Metal", 0, 3, 1), std::invalid_argument);
	EXPECT_THROW(new Truck("Audi", "Metal", 1, 2, 1), std::invalid_argument);
	EXPECT_THROW(new Truck("Audi", "Metal", 1, 3, 0), std::invalid_argument);

	Truck* ptr;
	EXPECT_NO_THROW(ptr = new Truck("Audi", "Metal", 1, 3, 1));
	delete ptr;
}

class TruckTest : public ::testing::Test
{
protected:
	TruckTest()
	{
		testPtr = new Truck("Audi", "Metal", 5, 18, 10);
	}

	Truck* testPtr;

	~TruckTest()
	{
		delete testPtr;
	}
};

TEST_F(TruckTest, test_construction_values_copied_correctly)
{
	CheckTruckProperties(testPtr, "Audi", "", 18, 10);
}
