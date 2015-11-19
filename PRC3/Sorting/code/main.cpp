#include <iostream>
#include <string>

#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

template <typename T>
inline bool generic_comparer(const T& a, const T& b)
{
	return a < b;
}

bool value_comparer(Value* a, Value* b)
{
	return generic_comparer(a->getText(), b->getText());
}

bool key_comparer(Key* a, Key* b)
{
	return generic_comparer(a->getText(), b->getText());
}

#include "QuickSort.h"
#include "BubbleSort.h"

Key* PerformQSort(Key* head)
{
	// sort all data
	// todo: your code here!
	Key* ckey = head;
	std::vector<Key*> keys;
	while (ckey)
	{
		//Add current key to keylist
		keys.push_back(ckey);

		//Get the values
		std::vector<Value*> values;
		Value* val = ckey->getValuePtr();
		while (val)
		{
			values.push_back(val);
			val = val->getNext();
		}

		//Sort values
		qSort(values, value_comparer);

		//Apply sorted values
		ckey->setValuePtr(values[0]);
		for (size_t i = 1; i < values.size(); ++i)
		{
			values[i - 1]->setNext(values[i]);
		}
		values[values.size() - 1]->setNext(NULL);

		//Go to next key (if any)
		ckey = ckey->getNext();
	}

	//sort the keys
	qSort(keys, key_comparer);

	//Apply sorted keys
	for (size_t i = 1; i < keys.size(); ++i)
	{
		keys[i - 1]->setNext(keys[i]);
	}
	keys[keys.size() - 1]->setNext(NULL);

	return keys[0];
}

Key* PerformBSort(Key* head)
{
	Key* ckey = head;
	while (ckey)
	{
		ckey->setValuePtr(BubbleSort2(ckey->getValuePtr()));
		//Go to next key (if any)
		ckey = ckey->getNext();
	}
	return BubbleSort2(head);
}

struct to_pass
{
	long step;
	long numCPU;
	Key* head;

	to_pass(long step, long numCPU, Key* head)
		: step(step), numCPU(numCPU), head(head)
	{ }
};

pthread_t threads[8];

inline Key* PerformSubSortStep(Key* curr, long howmany, long& counter)
{
	for (counter = 0; counter < howmany && curr; ++counter)
	{
		curr = curr->getNext();
	}
	return curr;
}

void *PerformSubSort(void* var)
{
	to_pass* data = (to_pass*)var;

	long countr;
	long step = data->step;
	long numCPU = data->numCPU;
	Key* ckey = PerformSubSortStep(data->head, step, countr);

	delete data;

	while (ckey)
	{
		ckey->setValuePtr(BubbleSort2(ckey->getValuePtr()));
		//Go to next key (if any)
		ckey = PerformSubSortStep(ckey, numCPU, countr);
	}

	return NULL;
}

/*

1 CPU: 4.52 4.67 4.52
2 CPU: 4.07 4.04 4.07
4 CPU: 4.95 4.97 4.96

*/
Key* PerformBSortThreaded(Key* head)
{
	long numCPU = sysconf(_SC_NPROCESSORS_ONLN);
	if (numCPU < 1) numCPU = 1;
	else
	if (numCPU > 8) numCPU = 8;

	if (numCPU > 1)
	{
		for (long i = 0; i < numCPU; ++i)
		{
			pthread_create(&threads[i], NULL, PerformSubSort, (void*)new to_pass(i, numCPU, head));
		}
		for (long i = 0; i < numCPU; ++i)
		{
			pthread_join(threads[i], NULL);
		}
		return BubbleSort2(head);
	}
	return PerformBSort(head);
}

int main()
{
    FileStructure f;
    Key head;

    f.loadFile("data/gibberish.bin", head);
	/*
	head.addValue("ac_ik");
	head.addValue("ac_ben");
	head.addValue("ac_meneer");
	head.addValue("ac_rafal");
	head.addValue("ac_meneer");
	head.addValue("ac_ben");
	head.addValue("ac_ik");

	head.addValue("ab_ik");
	head.addValue("ab_ben");
	head.addValue("ab_meneer");
	head.addValue("ab_rafal");
	head.addValue("ab_meneer");
	head.addValue("ab_ben");
	head.addValue("ab_ik");
	*/

	clock_t start, end;
	double cpu_time_used;

	start = clock();

	Key* new_head =
		PerformBSortThreaded(&head);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	std::cout << "Time: " << cpu_time_used << std::endl;
	//new_head->print();
    f.saveFile(*new_head, "sorted.bin");

    return 0;
}