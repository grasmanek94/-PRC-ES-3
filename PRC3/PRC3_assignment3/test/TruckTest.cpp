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
	EXPECT_THROW(new Truck("Audi", "Metal", 1, 3, 0), std::invalid_argument);

	Truck* ptr = NULL;
	EXPECT_NO_THROW(ptr = new Truck("Audi", "Metal", 1, 3, 1));
	delete ptr;
}

class TruckTest : public ::testing::Test
{
protected:
	TruckTest()
	{
		testPtr = new Truck("Audi", "Metal", 5, 18, 4);
		testPtr2 = new Truck("BMW", "Hout", 9, 25, 6);
	}

	Truck* testPtr;
	Truck* testPtr2;

	~TruckTest()
	{
		delete testPtr;
		testPtr = NULL;

		delete testPtr2;
		testPtr2 = NULL;
	}
};

TEST_F(TruckTest, test_construction_values_copied_correctly)
{
	CheckTruckProperties(testPtr, "Audi", "", 18, 4);
	CheckTruckProperties(testPtr2, "BMW", "", 25, 6);
}

TEST_F(TruckTest, test_construction_values_copied_correctly_copy_constructor)
{
	Truck* testPtr3 = new Truck(*testPtr2);

	CheckTruckProperties(testPtr2, "BMW", "", 25, 6);
	CheckTruckProperties(testPtr3, "BMW", "", 25, 6);

	delete testPtr3;
	testPtr3 = NULL;
}

TEST_F(TruckTest, test_assignment_operator)
{
	*testPtr = *testPtr2;

	CheckTruckProperties(testPtr, "BMW", "", 25, 6);
	CheckTruckProperties(testPtr2, "BMW", "", 25, 6);
}