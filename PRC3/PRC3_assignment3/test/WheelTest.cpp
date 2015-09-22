#include <string>
#include <stdexcept>
#include "gtest/gtest.h"

#include "Wheel.h"

static void CheckWheelProperties(Wheel* ptr, std::string material, int diameter)
{
	EXPECT_EQ(material, ptr->getMaterial());
	EXPECT_EQ(diameter, ptr->getDiameter());
}

TEST(WheelIllegalParameterTests, test_construction_exception)
{
	EXPECT_THROW(new Wheel(0, "Metal"), std::invalid_argument);

	Wheel* ptr = NULL;
	EXPECT_NO_THROW(ptr = new Wheel(1, "Metal"));
	delete ptr;
}

class WheelTest : public ::testing::Test
{
protected:
	WheelTest()
	{
		testPtr = new Wheel(5, "Metal");
		testPtr2 = new Wheel(6, "Rubber");
	}

	Wheel* testPtr;
	Wheel* testPtr2;

	~WheelTest()
	{
		delete testPtr;
		testPtr = NULL;

		delete testPtr2;
		testPtr2 = NULL;
	}
};

TEST_F(WheelTest, test_construction_values_copied_correctly)
{
	CheckWheelProperties(testPtr, "Metal", 5);
	CheckWheelProperties(testPtr2, "Rubber", 6);
}

TEST_F(WheelTest, test_set_material)
{
	testPtr->setMaterial("OtherMaterial");

	CheckWheelProperties(testPtr, "OtherMaterial", 5);
}