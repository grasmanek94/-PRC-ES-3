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

	Wheel* ptr;
	EXPECT_NO_THROW(ptr = new Wheel(1, "Metal"));
	delete ptr;
}

class WheelTest : public ::testing::Test
{
protected:
	WheelTest()
	{
		testPtr = new Wheel(5, "Metal");
	}

	Wheel* testPtr;

	~WheelTest()
	{
		delete testPtr;
	}
};

TEST_F(WheelTest, test_construction_values_copied_correctly)
{
	CheckWheelProperties(testPtr, "Metal", 5);
}