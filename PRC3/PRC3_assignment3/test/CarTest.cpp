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

	Car* ptr = NULL;
	EXPECT_NO_THROW(ptr = new Car("Audi", "Metal", 1, 3));
	delete ptr;
}

class CarTest : public ::testing::Test
{
protected:
	CarTest()
	{
		testPtr = new Car("Audi", "Metal", 10, 4);
		testPtr2 = new Car("BMW", "Hout", 16, 6);

	}

	Car* testPtr;
	Car* testPtr2;

	~CarTest()
	{
		delete testPtr;
		testPtr = NULL;

		delete testPtr2;
		testPtr2 = NULL;
	}
};

TEST_F(CarTest, test_construction_values_copied_correctly)
{
	CheckCarProperties(testPtr, "Audi", "", 4);
	CheckCarProperties(testPtr2, "BMW", "", 6);
}

TEST_F(CarTest, test_construction_values_copied_correctly_copy_constructor)
{
	Car* testPtr3 = new Car(*testPtr2);

	CheckCarProperties(testPtr3, "BMW", "", 6);
	CheckCarProperties(testPtr2, "BMW", "", 6);

	delete testPtr3;
	testPtr3 = NULL;
}

TEST_F(CarTest, test_set_licence_plate)
{
	testPtr->setLicencePlate("AA-BB-CC-ZZ");

	CheckCarProperties(testPtr, "Audi", "AA-BB-CC-ZZ", 4);
}

TEST_F(CarTest, test_assignment_operator)
{
	*testPtr = *testPtr2;
	CheckCarProperties(testPtr, "BMW", "", 6);
	CheckCarProperties(testPtr2, "BMW", "", 6);

	for (size_t i = 0; i < testPtr->getNrWheels(); ++i)
	{
		ASSERT_NE(testPtr->getWheel(i), testPtr2->getWheel(i));
	}

	{
		*testPtr = Car("Renault", "Aluminium", 6, 4);
	}
	CheckCarProperties(testPtr, "Renault", "Aluminium", 4);
}

TEST_F(CarTest, test_remove_wheel_0)
{
	testPtr->removeWheel(0);

	CheckCarProperties(testPtr, "Audi", "", 3);
}

TEST_F(CarTest, test_remove_wheel_last)
{
	testPtr->removeWheel(testPtr->getNrWheels() - 1);

	CheckCarProperties(testPtr, "Audi", "", 3);
}

TEST_F(CarTest, test_remove_wheel_all)
{
	while (testPtr->getNrWheels())
	{
		testPtr->removeWheel(0);
	}

	CheckCarProperties(testPtr, "Audi", "", 0);
}

TEST_F(CarTest, test_remove_wheel_too_much)
{
	while (testPtr->getNrWheels())
	{
		testPtr->removeWheel(0);
	}

	EXPECT_THROW(testPtr->removeWheel(0), std::out_of_range);

	CheckCarProperties(testPtr, "Audi", "", 0);
}

TEST_F(CarTest, test_remove_wheel_invalid)
{
	EXPECT_THROW(testPtr->removeWheel(testPtr->getNrWheels()), std::out_of_range);

	CheckCarProperties(testPtr, "Audi", "", 4);
}

TEST_F(CarTest, test_add_wheel_invalid)
{
	EXPECT_THROW(testPtr->addWheel(0, "Hout"), std::invalid_argument);

	CheckCarProperties(testPtr, "Audi", "", 4);
}

TEST_F(CarTest, test_add_wheel)
{
	testPtr->addWheel(1, "Hout");

	CheckCarProperties(testPtr, "Audi", "", 5);
}