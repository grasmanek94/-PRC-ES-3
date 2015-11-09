#ifndef SCAN_H
#define SCAN_H 

class Scan
{
private:
	int serialNumber;
	int timesRecycled;
	Scan* next;

public:
	Scan(int number);
	// pre:  -
	// post: serialNumber == number and timesRecycled == 0

	virtual ~Scan();
	// pre:  -
	// post: object has been destructed

	int getSerialNumber() const;
	// pre:  -
	// post: serialNumber has been returned

	Scan* getNext();
	// pre:  -
	// post: next scan has been returned

	void setNext(Scan* nextScan);
	// pre:  -
	// post: next points to nextScan

	void recycle();
	// pre:  -
	// post: timesRecycled has been increased by one

	int getTimesRecycled() const;
	// pre: -
	// post: timesRecycled has been returned
};

#endif
