#include <iostream>

#include "ScanList.h"

//Scan* head; // pointer to linked list of Scans

ScanList::ScanList()
{

}
// pre:  -
// post: list is empty

ScanList::~ScanList()
{
	if (head)
	{
		do
		{
			Scan* next = head->getNext();
			delete head;
			head = next;			
		} while (head);
	}
}
// pre:  -
// post: all scans have been destructed without memory leaks

void ScanList::addScan(int serialNumber)
{
	if (head)
	{
		bool add_new = false;
		Scan* current = head;
		Scan* previous = NULL;

		while (current && serialNumber > current->getSerialNumber())
		{
			previous = current;
			current = current->getNext();
		}

		if (current)
		{
			if (current->getSerialNumber() == serialNumber)
			{
				current->recycle();
			}
			else if(current->getSerialNumber() > serialNumber)
			{
				add_new = true;
			}
			else
			{
				throw std::exception(/*"This should be impossible, if this happens the sorting fails or someone modified the pointer in Scan manually"*/);
			}
		}
		else
		{
			add_new = true;
		}

		if (add_new)
		{
			Scan* new_scan = new Scan(serialNumber);
			if (previous == NULL)
			{			
				new_scan->setNext(head);
				head = new_scan;
			}
			else
			{
				new_scan->setNext(current);
				previous->setNext(new_scan);
			}
		}
	}
	else
	{
		head = new Scan(serialNumber);
	}
}
// pre:  serialNumbers in the linked list are in ascending order
// post: IF serialNumber is not present in the list
// THEN a new scan with serialNumber has been added in the right place
//      to the list
// ELSE timesRecycled has been increased by one

Scan* ScanList::getScanByNr(int position)
{
	if (!head)
	{
		return NULL;
	}

	Scan* current = head;
	size_t counter = 0;

	while (position > counter && current)
	{
		++counter;
		current = current->getNext();
	}

	return current;
}
// pre:  -
// post: IF 0 <= position < nr of scans in the list
// THEN return a pointer to the scan at that position
// ELSE return NULL

bool ScanList::removeScan(int serialNumber)
{
	if (!head)
	{
		return false;
	}

	Scan* current = head;
	Scan* previous = NULL;

	while (current && serialNumber > current->getSerialNumber())
	{
		previous = current;
		current = current->getNext();
	}

	if (current && current->getSerialNumber() == serialNumber)
	{
		if (previous)
		{
			previous->setNext(current->getNext());
		}
		else
		{
			head = head->getNext();
		}

		delete current;
		current = NULL;
	}
 
	return false;
}
// pre:  serialNumbers are in ascending order in linked list scans
// post: IF serialNumber is present in the list
// THEN scan has been removed from the list and true has been returned
// ELSE false has been returned

int ScanList::getTimesRecycled(int serialNumber)
{
	if (!head)
	{
		return 0;
	}

	Scan* current = head;

	while (current && serialNumber > current->getSerialNumber())
	{
		current = current->getNext();
	}

	if (current)
	{
		if (current->getSerialNumber() == serialNumber)
		{
			return current->getTimesRecycled();
		}
		else if (current->getSerialNumber() > serialNumber)
		{
			return 0;
		}
		else
		{
			throw std::exception(/*"This should be impossible, if this happens the sorting fails or someone midified the pointer in Scan manually"*/);
		}
	}

	return 0;
}
// pre:  serialNumbers in linked list scans are in ascending order
// post: IF a scan with serialNumber is present in the list
// THEN return the value of timesRecycled of that scan
// ELSE return 0