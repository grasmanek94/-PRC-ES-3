#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <stdio.h>

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
T* BubbleSort(T* begin) 
{
	int lengte = AmountOfElements(begin);
	int i, j;
	T* at_i;
	T* at_imo;
	T* at_imt;

	for (j = 0; j < lengte; j++) 
	{
		for (i = 1; i < lengte - j; i++) 
		{
			if (i == 1)
			{
				at_imt = NULL;
				at_imo = GetAt(begin, i - 1);
			}
			else
			{
				at_imt = GetAt(begin, i - 2);
				at_imo = at_imt->getNext();
			}
			at_i = at_imo->getNext();

			if (at_imo->getText() > at_i->getText())
			{
				if (at_imo == begin)
				{
					//begin -> at_imo -> begin->getNext()
					begin = at_i;
					at_imo->setNext(at_i->getNext());
					at_i->setNext(at_imo);
				}
				else
				{
					//at_imt -> at_i -> at_imo -> at_i->getNext()
					at_imo->setNext(at_i->getNext());
					at_i->setNext(at_imo);
					at_imt->setNext(at_i);
				}
			}
		}
	}

	return begin;
}

template <typename T>
T* BubbleSort2(T* begin)
{
	bool swapped = true;
	while(swapped)
	{
		T* previous = NULL;
		T* current = begin;
		swapped = false;
		while(current)
		{
			T* next = current->getNext();

			if (next)
			{
				if (current->getText() > next->getText())
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
#endif