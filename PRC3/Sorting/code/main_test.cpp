#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

#include "MergeSort.h"

#include <cstring>
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

Key* timeSort(const std::string& name, size_t i, Key*(*key)(Key*), Value*(*value)(Value*))
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
		ckey->setValuePtr(value(ckey->getValuePtr()));
		ckey = ckey->getNext();
	}
	new_head = key(head);

	timemeasure.Stop();
	std::cout << name << "[" << i << "]: " << timemeasure.Elapsed() * 1000.0 << " ms" << std::endl;

	return new_head;
}

int main()
{
	FileStructure f;

	const size_t amount_of_test = 8;
	const size_t max_test = 4;

	size_t current_test = 0;
	Key* test[max_test][amount_of_test];
	memset(test, 0, sizeof(test));

	for (size_t i = 0; i < amount_of_test; ++i)
	{
		test[current_test][i] = timeSort("Sort", i, MergeSort::Sort<Key>, MergeSort::Sort<Value>);
	}

	++current_test;

	for (size_t i = 0; i < amount_of_test; ++i)
	{
		test[current_test][i] = timeSort("Sort2", i, MergeSort::Sort2<Key>, MergeSort::Sort2<Value>);
	}

	++current_test;

	for (size_t i = 0; i < amount_of_test; ++i)
	{
		test[current_test][i] = timeSort("Sort3", i, MergeSort::Sort3<Key>, MergeSort::Sort3<Value>);
	}

	++current_test;

	for (size_t i = 0; i < amount_of_test; ++i)
	{
		test[current_test][i] = timeSort("SortMT", i, MergeSort::TM_MergeSort<Key>, MergeSort::TM_MergeSort<Value>);
	}

	for (size_t i = 0; i < max_test; ++i)
	{
		//std::string savename = "0_sorted.bin";
		//savename[0] += i;
		//f.saveFile(*test[i][0], savename);

		for (size_t j = 0; j < amount_of_test; ++j)
		{
			if (test[i][j])
			{
				delete test[i][j];
				test[i][j] = NULL;
			}
		}
	}

	return 0;
}