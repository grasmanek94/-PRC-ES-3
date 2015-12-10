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

/*
Sort[0]: 109.989 ms
Sort[1]: 113.265 ms
Sort[2]: 107.484 ms
Sort[3]: 107.474 ms
Sort[4]: 107.166 ms
Sort[5]: 110.212 ms
Sort[6]: 106.953 ms
Sort[7]: 107.931 ms
Sort2[0]: 98.454 ms
Sort2[1]: 98.327 ms
Sort2[2]: 98.193 ms
Sort2[3]: 97.855 ms
Sort2[4]: 97.725 ms
Sort2[5]: 97.634 ms
Sort2[6]: 98.819 ms
Sort2[7]: 97.615 ms
Sort3[0]: 101.94 ms
Sort3[1]: 101.976 ms
Sort3[2]: 108.967 ms
Sort3[3]: 102.177 ms
Sort3[4]: 102.039 ms
Sort3[5]: 100.956 ms
Sort3[6]: 100.834 ms
Sort3[7]: 101.016 ms
SortMT[0]: 106.536 ms
SortMT[1]: 106.284 ms
SortMT[2]: 106.779 ms
SortMT[3]: 107.035 ms
SortMT[4]: 109.01 ms
SortMT[5]: 106.845 ms
SortMT[6]: 107.293 ms
SortMT[7]: 106.433 ms

*/