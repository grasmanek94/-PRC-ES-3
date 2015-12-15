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

	//nonrecursive
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

	//TM_ sort code is van MinhTriet (MT omgedraaid hehe) om te vergelijken met mijne
	template <class T>
	T* TM_GetMiddle(T* head) {
		if (head == NULL) {
			return head;
		}
		//std::cout << "Getting middle" << std::endl;

		T* slow = NULL;
		T* fast = NULL;
		slow = fast = head;
		while (fast->getNext() != NULL && fast->getNext()->getNext() != NULL) {
			slow = slow->getNext();
			fast = fast->getNext()->getNext();
		}
		return slow;
	}

	template <class T>
	T* TM_Merge(T* firstNode, T* secondNode)
	{
		if (firstNode == NULL) return secondNode;
		else if (secondNode == NULL) return firstNode;
		else if (firstNode->getText() <= secondNode->getText()) //if I reverse the sign to >=, the behavior reverses
		{
			firstNode->setNext(TM_Merge(firstNode->getNext(), secondNode));
			return firstNode;
		}
		else
		{
			secondNode->setNext(TM_Merge(firstNode, secondNode->getNext()));
			return secondNode;
		}
	}
	/*
	* Merge sort
	*/
	template <class T>
	T* TM_MergeSort(T* head) {
		if (head == NULL || head->getNext() == NULL) {
			return head;
		}
		T* middle = TM_GetMiddle(head);
		//std::cout << "Got middle: " << middle->getText() << std::endl;

		T* sHalf = middle->getNext();
		//std::cout << "Got thing: " << sHalf->getText() << std::endl;

		middle->setNext(NULL);
		return TM_Merge(TM_MergeSort(head), TM_MergeSort(sHalf));
	}

	/* 
				-O0			-O3

	Sort[0]  :	56.361 ms	50.071 ms
	Sort[1]  :	51.548 ms	47.656 ms
	Sort[2]  :	51.225 ms	45.964 ms
	Sort[3]  :	56.113 ms	45.343 ms
	Sort[4]  :	54.049 ms	44.098 ms
	Sort[5]  :	51.668 ms	49.451 ms
	Sort[6]  :	53.373 ms	44.509 ms
	Sort[7]  :	50.890 ms	43.721 ms

	gem:		53.153 ms	46.352 ms

	Sort2[0] :	48.554 ms	40.834 ms
	Sort2[1] :	45.433 ms	43.086 ms
	Sort2[2] :	46.484 ms	40.579 ms
	Sort2[3] :	46.677 ms	39.476 ms
	Sort2[4] :	47.311 ms	40.691 ms
	Sort2[5] :	45.758 ms	40.865 ms
	Sort2[6] :	47.734 ms	41.925 ms
	Sort2[7] :	45.565 ms	44.066 ms

	gem:		46.690 ms	41.440 ms

	Sort3[0] :	48.503 ms	41.392 ms
	Sort3[1] :	58.640 ms	42.249 ms
	Sort3[2] :	48.442 ms	40.869 ms
	Sort3[3] :	49.619 ms	49.838 ms
	Sort3[4] :	52.041 ms	41.052 ms
	Sort3[5] :	49.496 ms	40.542 ms
	Sort3[6] :	47.877 ms	41.247 ms
	Sort3[7] :	47.953 ms	41.151 ms

	gem:		50.321 ms	42.293 ms

	SortMT[0]:	52.017 ms	44.344 ms
	SortMT[1]:	49.655 ms	43.756 ms
	SortMT[2]:	51.707 ms	42.996 ms
	SortMT[3]:	49.049 ms	45.802 ms
	SortMT[4]:	49.625 ms	43.515 ms
	SortMT[5]:	50.244 ms	42.458 ms
	SortMT[6]:	49.141 ms	43.519 ms
	SortMT[7]:	51.132 ms	45.256 ms

	gem:		50.321 ms	43.956 ms
	*/
}
#endif