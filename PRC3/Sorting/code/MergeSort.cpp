#include <pthread.h>
#include <unistd.h>

#include "Key.h"
#include "Value.h"

#include "MergeSort.h"

namespace MergeSort
{
	Key* PerformSort(Key* head)
	{
		Key* ckey = head;
		while (ckey)
		{
			ckey->setValuePtr(MergeSort::Sort(ckey->getValuePtr()));
			ckey = ckey->getNext();
		}
		return MergeSort::Sort(head);
	}
}