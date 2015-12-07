#ifndef MERGESORT_H
#define MERGESORT_H

#include "Compare.h"
#include "Key.h"

namespace MergeSort
{

	template <typename KV>
	KV* Split(KV* elem)
	{
		KV* sn;

		if (elem == NULL)
		{
			return NULL;
		}
		else if (elem->getNext() == NULL)
		{
			return NULL;
		}
		else
		{
			sn = elem->getNext();
			elem->setNext(sn->getNext());
			sn->setNext(Split(sn->getNext()));
			return sn;
		}
	}

	template <typename KV>
	KV* Merge(KV* fn, KV* sn)
	{
		if (fn == NULL)
		{
			return sn;
		}
		else if (sn == NULL)
		{
			return fn;
		}
		else if (!kv_comparer(fn, sn))
		{
			fn->setNext(Merge(fn->getNext(), sn));
			return fn;
		}
		else
		{
			sn->setNext(Merge(fn, sn->getNext()));
			return sn;
		}
	}

	template <typename KV>
	KV* Sort(KV *elem)
	{
		KV *sn;

		if (elem == NULL)
		{
			return NULL;
		}
		else if (elem->getNext() == NULL)
		{
			return elem;
		}
		else
		{
			sn = Split(elem);
			return Merge(Sort(elem), Sort(sn));
		}
	}

	Key* PerformSort(Key* head);
	//Key* PerformSortThreaded(Key* head);//todo?
}
#endif