#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

#include "MergeSort.h"

#include <iostream>
#include <time.h>
class TM
{
private:
	clock_t start;
	clock_t end;
	double cpu_time_used;
public:
	TM()
		: start(0), end(0), cpu_time_used(0.0)
	{ }

	void Start()
	{
		start = clock();
	}

	void Stop()
	{
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	}

	double Elapsed()
	{
		return cpu_time_used;
	}
};

TM timemeasure;


int main()
{
	FileStructure f;
	Key* head = new Key();
	Key* ckey = NULL;
	Key* new_head = NULL;

	f.loadFile("data/gibberish.bin", *head);
	timemeasure.Start();

	ckey = head;
	while (ckey)
	{
		ckey->setValuePtr(MergeSort::Sort3(ckey->getValuePtr()));
		ckey = ckey->getNext();
	}
	new_head = MergeSort::Sort3(head);

	timemeasure.Stop();

	std::cout << timemeasure.Elapsed() * 1000.0 << " ms" << std::endl;

	f.saveFile(*new_head, "sorted.bin");

	delete new_head;

	return 0;
}