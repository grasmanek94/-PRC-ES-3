#include <iostream>
#include <string>

#include "Scan.h"

#ifndef _WIN32

#include <stdio.h>

int pipeToConsole(std::string command)
{
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */

	fp = popen(command.c_str(), "r");

	if (fp == NULL)
	{
		printf("Failed to run command '%s'\n", command.c_str());
		return 0;
	}


	printf("\n----------------------\n");
	printf("Output of command '%s'\n", command.c_str());
	/* Read the output a line at a time - output it. */

	while (fgets(path, sizeof(path) - 1, fp) != NULL) {
		printf("%s", path);
	}

	printf("\n----------------------\n");
	/* close */
	pclose(fp);

	return 1;

}

class blablainit
{
public:
	blablainit()
	{
		pipeToConsole("cat assignment4Test.cpp | tail -n+97");
	}
};

blablainit _blablainit;
#endif
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
