#include <pthread.h>
#include <unistd.h>

#include "Key.h"
#include "Value.h"

#include "BubbleSort.h"

namespace BubbleSort
{
	Key* PerformSort(Key* head)
	{
		Key* ckey = head;
		while (ckey)
		{
			ckey->setValuePtr(BubbleSort::Sort(ckey->getValuePtr()));
			ckey = ckey->getNext();
		}
		return BubbleSort::Sort(head);
	}

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
		mt_to_pass* data = (mt_to_pass*)var;

		long countr;
		long step = data->step;
		long numCPU = data->numCPU;
		Key* ckey = PerformSubSortStep(data->head, step, countr);

		delete data;

		while (ckey)
		{
			ckey->setValuePtr(BubbleSort::Sort(ckey->getValuePtr()));
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
	Key* PerformSortThreaded(Key* head)
	{
		long numCPU = (long)((double)sysconf(_SC_NPROCESSORS_ONLN) * 0.75);
		if (numCPU < 1) numCPU = 1;
		else
			if (numCPU > 8) numCPU = 8;

		if (numCPU > 1)
		{
			for (long i = 0; i < numCPU; ++i)
			{
				pthread_create(&threads[i], NULL, PerformSubSort, (void*)new BubbleSort::mt_to_pass(i, numCPU, head));
			}
			for (long i = 0; i < numCPU; ++i)
			{
				pthread_join(threads[i], NULL);
			}
			return BubbleSort::Sort(head);
		}
		return PerformSort(head);
	}
}