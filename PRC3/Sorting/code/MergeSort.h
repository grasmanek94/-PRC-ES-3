#ifndef MERGESORT_H
#define MERGESORT_H

namespace MergeSort
{
	template <typename KV>
	KV* Split(KV* elem)
	{
		if (elem == NULL)
		{
			return NULL;
		}

		KV* sn = elem->getNext();

		if (sn == NULL)
		{
			return NULL;
		}

		elem->setNext(sn->getNext());
		sn->setNext(Split(sn->getNext()));
		return sn;
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
		else if (fn->getText() > sn->getText())
		{
			sn->setNext(Merge(fn, sn->getNext()));
			return sn;
		}
		else
		{
			fn->setNext(Merge(fn->getNext(), sn));
			return fn;
		}
	}

	template <typename KV>
	KV* Sort(KV *elem)
	{
		if (elem == NULL || elem->getNext() == NULL)
		{
			return elem;
		}

		return Merge(Sort(elem), Sort(Split(elem)));
	}
}
#endif