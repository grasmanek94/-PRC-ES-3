#include <iostream>

#include "ScanList.h"

int main()
{
	ScanList* list = new ScanList();

	list->removeScan(999);
	list->removeScan(0);

	list->addScan(10);
	list->removeScan(999);
	list->removeScan(0);
	
	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;

	list->addScan(5);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(1)->getSerialNumber() << std::endl;

	list->addScan(7);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(1)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(2)->getSerialNumber() << std::endl;

	list->addScan(12);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(1)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(2)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(3)->getSerialNumber() << std::endl;

	list->removeScan(12);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(1)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(2)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(3) << std::endl;

	list->addScan(12);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(1)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(2)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(3)->getSerialNumber() << std::endl;

	list->removeScan(10);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(1)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(2)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(3) << std::endl;

	list->removeScan(5);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(1)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(2) << std::endl;
	std::cout << list->getScanByNr(3) << std::endl;

	list->removeScan(12);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0)->getSerialNumber() << std::endl;
	std::cout << list->getScanByNr(1) << std::endl;
	std::cout << list->getScanByNr(2) << std::endl;
	std::cout << list->getScanByNr(3) << std::endl;

	list->removeScan(7);

	std::cout << "---" << std::endl;
	std::cout << list->getScanByNr(0) << std::endl;
	std::cout << list->getScanByNr(1) << std::endl;
	std::cout << list->getScanByNr(2) << std::endl;
	std::cout << list->getScanByNr(3) << std::endl;

	//5: 3, 2 times recycled
	//7: 4, 3 times recycled
	//10:5, 4 times recycled
	//12:6, 5 times recycled
	list->addScan(10);
	list->addScan( 5);
	list->addScan(12);
	list->addScan( 7);
	list->addScan( 5);
	list->addScan(10);
	list->addScan(12);
	list->addScan( 5);
	list->addScan( 7);
	list->addScan(10);
	list->addScan(12);
	list->addScan(12);
	list->addScan( 7);
	list->addScan(12);
	list->addScan( 7);
	list->addScan(12);
	list->addScan(10);
	list->addScan(10);

	std::cout << "---" << std::endl;
	std::cout << list->getTimesRecycled(5) << std::endl;
	std::cout << list->getTimesRecycled(7) << std::endl;
	std::cout << list->getTimesRecycled(10) << std::endl;
	std::cout << list->getTimesRecycled(12) << std::endl;

	while (true);
	return 0;
}