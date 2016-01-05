#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

template <typename T>
void qSort(std::vector<T>& vec, int L, int R, bool(*comparer)(T, T))
{		
	if (L < R)
	{
		int pp = qSortPart(vec, L, R, comparer);
		qSort(vec, L, pp - 1, comparer);
		qSort(vec, pp + 1, R, comparer);
	}
}

template <typename T>
void qSort(std::vector<T>& vec, bool(*comparer)(T, T))
{
	qSort(vec, 0, vec.size() - 1, comparer);
}

template <typename T>
int qSortPart(std::vector<T>& arr, int L, int R, bool(*comparer)(T, T))
{
	T pv = arr[L];
	int pp = L;

	for (int i = L + 1; i <= R; i++)
	{
		if (comparer(arr[i],pv))
		{
			std::swap(arr[pp + 1], arr[i]);
			std::swap(arr[pp], arr[pp + 1]);
			pp++;
		}
	}
	return pp;
}

#endif