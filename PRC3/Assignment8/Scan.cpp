#include <iostream>
#include <string>

#include "Scan.h"

//	int serialNumber;
//	int timesRecycled;
//	Scan* next;

Scan::Scan(int number)
{
	serialNumber = number;
	timesRecycled = 0;
	next = NULL;
}
// pre:  -
// post: serialNumber == number and timesRecycled == 0

Scan::~Scan()
{
	
}
// pre:  -
// post: object has been destructed

int Scan::getSerialNumber() const
{
	return serialNumber;
}
// pre:  -
// post: serialNumber has been returned

Scan* Scan::getNext()
{
	return next;
}
// pre:  -
// post: next scan has been returned

void Scan::setNext(Scan* nextScan)
{
	next = nextScan;
}
// pre:  -
// post: next points to nextScan

void Scan::recycle()
{
	++timesRecycled;
}
// pre:  -
// post: timesRecycled has been increased by one

int Scan::getTimesRecycled() const
{
	return timesRecycled;
}
// pre: -
// post: timesRecycled has been returned
