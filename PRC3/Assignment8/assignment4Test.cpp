#include <stdexcept>
#include <string>
#include <gtest/gtest.h>

#include "Scan.h"
#include "ScanList.h"

int serials[] = { 1864, 457, 67324, 1, 134, 12, 9776, 9777 };
int nrSerials = sizeof(serials) / sizeof(serials[0]);

ScanList* createTestList()
{
	ScanList* p = new ScanList();
	for (int i = 0; i < nrSerials; ++i)
	{
		p->addScan(serials[i]);
	}
	return p;
}

TEST(Test, test_black_box_1)
{
	// test_Construction
	{
		Scan s(100);
		ASSERT_EQ(100, s.getSerialNumber());
		ASSERT_EQ(0, s.getTimesRecycled());
		ASSERT_EQ(NULL, s.getNext());
		Scan t(123456789);
		ASSERT_EQ(123456789, t.getSerialNumber());
	}

	// test_Next
	{
		Scan s(123);
		s.setNext(&s);
		ASSERT_EQ(&s, s.getNext());
	}

	// test_timesRecycled
	{
		Scan s(432);
		s.recycle();
		ASSERT_EQ(1, s.getTimesRecycled());
		for (int i = 0; i < 1000; i++)
		{
			s.recycle();
		}
		ASSERT_EQ(1001, s.getTimesRecycled());
	}

	// test_1_scan
	{
		ScanList *p = new ScanList();
		p->addScan(1234);
		Scan* s = p->getScanByNr(0);
		std::cout << s->getNext() << std::endl;

		ASSERT_FALSE(s == NULL);

		EXPECT_EQ(1234, s->getSerialNumber());
		EXPECT_EQ(0, s->getTimesRecycled());
		delete p;
		p = NULL;
	}

	// test_getScanByNr_exceptions
	{
		ScanList *p = new ScanList();

		EXPECT_EQ(NULL, p->getScanByNr(-1));
		EXPECT_EQ(NULL, p->getScanByNr(0));
		EXPECT_EQ(NULL, p->getScanByNr(1));

		p->addScan(1);
		EXPECT_FALSE(NULL == p->getScanByNr(0));

		delete p;
		p = NULL;
	}

	// test_sorted_scans
	{
		ScanList* p = createTestList();

		int sortedSerials[] = { 1, 12, 134, 457, 1864, 9776, 9777, 67324 };
		int nrSortedSerials = sizeof(sortedSerials) / sizeof(sortedSerials[0]);

		for (int i = 0; i < nrSortedSerials; ++i)
		{
			Scan* s = p->getScanByNr(i);
			ASSERT_FALSE(s == NULL);

			EXPECT_EQ(sortedSerials[i], s->getSerialNumber()) << " i is: " << i;
		}

		delete p;
		p = NULL;
	}

	// test_removeScan_non_existing
	{
		ScanList* p = createTestList();

		EXPECT_FALSE(p->removeScan(-1));
		EXPECT_FALSE(p->removeScan(0));
		EXPECT_FALSE(p->removeScan(1000));
		EXPECT_FALSE(p->removeScan(123456));

		delete p;
		p = NULL;
	}

	// test_removeScan_existing_values
	{
		ScanList* p = createTestList();

		EXPECT_TRUE(p->removeScan(12));
		EXPECT_TRUE(p->removeScan(9776));
		EXPECT_TRUE(p->removeScan(1));
		EXPECT_TRUE(p->removeScan(67324));

		int remaining[] = { 134, 457, 1864, 9777 };
		int nrRemaining = sizeof(remaining) / sizeof(remaining[0]);

		int i = 0;
		for (; i < nrRemaining; ++i)
		{
			Scan* s = p->getScanByNr(i);
			ASSERT_FALSE(s == NULL);

			EXPECT_EQ(remaining[i], s->getSerialNumber()) << " i is: " << i;
		}

		Scan* s = p->getScanByNr(i);
		ASSERT_TRUE(s == NULL);

		delete p;
		p = NULL;
	}

	// test_getTimesRecycled
	{
		ScanList* p = createTestList();

		for (int i = 0; i < nrSerials; ++i)
		{
			Scan* s = p->getScanByNr(i);
			ASSERT_FALSE(s == NULL);

			EXPECT_EQ(0, p->getTimesRecycled(serials[i])) << " i is: " << i;
		}

		p->addScan(457);
		p->addScan(1);
		p->addScan(1);
		p->addScan(67324);
		p->addScan(67324);
		p->addScan(67324);

		EXPECT_EQ(1, p->getTimesRecycled(457));
		EXPECT_EQ(2, p->getTimesRecycled(1));
		EXPECT_EQ(3, p->getTimesRecycled(67324));

		delete p;
		p = NULL;
	}
}