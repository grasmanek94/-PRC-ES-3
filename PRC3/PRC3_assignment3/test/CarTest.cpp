#include <string>
#include <stdexcept>
#include "gtest/gtest.h"

#include "Car.h"

static void CheckCarProperties(Car* ptr, std::string model, std::string licencePlate, int wheels)
{
	EXPECT_EQ(model, ptr->getModel());
	EXPECT_EQ(licencePlate, ptr->getLicencePlate());
	EXPECT_EQ(wheels, ptr->getNrWheels());
}

TEST(CarIllegalParameterTests, test_construction_exception)
{
	EXPECT_THROW(new Car("Audi", "Metal", 0, 3), std::invalid_argument);
	EXPECT_THROW(new Car("Audi", "Metal", 1, 2), std::invalid_argument);

	Car* ptr;
	EXPECT_NO_THROW(ptr = new Car("Audi", "Metal", 1, 3));
	delete ptr;
}

class CarTest : public ::testing::Test
{
protected:
	CarTest()
	{
		testPtr = new Car("Audi", "Metal", 10, 4);
	}

	Car* testPtr;

	~CarTest()
	{
		delete testPtr;
	}
};

TEST_F(CarTest, test_construction_values_copied_correctly)
{
	CheckCarProperties(testPtr, "Audi", "", 4);
}
