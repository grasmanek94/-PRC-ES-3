#ifndef MERGESORT_H
#define MERGESORT_H

namespace MergeSort
{
	//recursive multiple functions
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

	//recursive multiple functions
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

	//recursive multiple functions
	template <typename KV>
	KV* Sort(KV *elem)
	{
		if (elem == NULL || elem->getNext() == NULL)
		{
			return elem;
		}

		return Merge(Sort(elem), Sort(Split(elem)));
	}

	//recursive one function
	template <typename KV>
	KV* Sort2(KV* elem)
	{
		if (!elem || !elem->getNext())
		{
			return elem;
		}

		KV* right = elem;
		KV* temp = elem;
		KV* last = elem;
		KV* result = NULL;
		KV* next = NULL;
		KV* tail = NULL;

		while (temp && temp->getNext())
		{
			last = right;
			right = right->getNext();
			temp = temp->getNext()->getNext();
		}

		last->setNext(NULL);

		elem = Sort2(elem);
		right = Sort2(right);

		while (elem || right)
		{
			if (!right)
			{
				next = elem;
				elem = elem->getNext();
			}
			else if (!elem) 
			{
				next = right;
				right = right->getNext();
			}
			else if (elem->getText() < right->getText()) 
			{
				next = elem;
				elem = elem->getNext();
			}
			else {
				next = right;
				right = right->getNext();
			}
			if (!result) 
			{
				result = next;
			}
			else 
			{
				tail->setNext(next);
			}
			tail = next;
		}
		return result;
	}

	//nonrecursive, seems to be the fastest, and ofcourse most complex to explain and implement >_>
	template <typename KV>
	KV* Sort3(KV* elem)
	{
		int listSize = 1;
		int numMerges = 0;
		int leftSize = 0;
		int rightSize = 0;

		KV* tail = NULL;
		KV* left = NULL;
		KV* right = NULL;
		KV* next = NULL;

		if (!elem || !elem->getNext())
		{
			return elem; 
		}

		do 
		{ 
			numMerges = 0;
			left = elem;
			tail = NULL;
			elem = NULL;

			while (left) 
			{ 

				numMerges++;
				right = left;
				leftSize = 0;
				rightSize = listSize;

				while (right && leftSize < listSize)
				{
					leftSize++;
					right = right->getNext();
				}
				while (leftSize>0 || (rightSize>0 && right)) 
				{
					if (!leftSize) 
					{
						next = right; 
						right = right->getNext(); 
						rightSize--; 
					}
					else if (!rightSize || !right) 
					{ 
						next = left; 
						left = left->getNext(); 
						leftSize--; 
					}
					else if (left->getText() < right->getText()) 
					{ 
						next = left; 
						left = left->getNext();
						leftSize--;
					}
					else 
					{ 
						next = right; 
						right = right->getNext(); 
						rightSize--; 
					}
					if (tail)
					{
						tail->setNext(next);
					}
					else
					{
						elem = next;
					}
					tail = next;
				}
				left = right;
			}
			tail->setNext(NULL);
			listSize <<= 1;
		}
		while (numMerges>1);
		return elem;
	}
}
#endif