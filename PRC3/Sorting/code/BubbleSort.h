#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <stdio.h>
#include "Compare.h"

namespace BubbleSort
{
	template <typename T>
	T* GetAt(T* begin, int index)
	{
		if (index < 0)
		{
			return NULL;
		}

		T* current = begin;
		int counter = 0;
		while (counter++ < index && current)
		{
			current = current->getNext();
		}

		return current;
	}

	template <typename T>
	int AmountOfElements(T* begin)
	{
		int counter = 0;
		while (begin)
		{
			++counter;
			begin = begin->getNext();
		}

		return counter;
	}

	template <typename T>
	void PrintAll(T* begin)
	{
		while (begin)
		{
			begin->print();
			printf("\n");
			begin = begin->getNext();
		}
	}

	template <typename T>
	void SwapTwoAndThree(T* n_1, T* n_2, T* n_3, T* n_4)
	{
		if (n_1 != n_3)
		{
			n_1->setNext(n_3);
		}
		n_2->setNext(n_4);
		n_3->setNext(n_2);
	}

	template <typename T>
	T* Sort(T* begin)
	{
		bool swapped = true;
		while (swapped)
		{
			T* previous = NULL;
			T* current = begin;
			swapped = false;
			while (current)
			{
				T* next = current->getNext();

				if (next)
				{
					if (kv_comparer(current, next))
					{
						swapped = true;
						if (current == begin)
						{
							//(begin)current->next->last
							//			V
							//(begin)next->current->last
							T* last = next->getNext();
							current->setNext(last);
							next->setNext(current);
							begin = next;

							previous = next;
						}
						else
						{
							//previous->current->next->last
							//			V
							//previous->next->current->last
							T* last = next->getNext();
							current->setNext(last);
							next->setNext(current);
							previous->setNext(next);

							previous = next;
						}
					}
					else
					{
						previous = current;
						current = next;
					}
				}
				else
				{
					current = NULL;
				}
			}
		}

		return begin;
	}

	struct mt_to_pass
	{
		long step;
		long numCPU;
		Key* head;

		mt_to_pass(long step, long numCPU, Key* head)
			: step(step), numCPU(numCPU), head(head)
		{ }
	};

	Key* PerformSort(Key* head);
	Key* PerformSortThreaded(Key* head);
}
#endif