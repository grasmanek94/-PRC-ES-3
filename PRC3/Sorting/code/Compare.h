#ifndef COMPARE_H
#define COMPARE_H

#include "Value.h"
#include "Key.h"

template <typename T>
inline bool generic_comparer(const T& a, const T& b)
{
	return a > b;
}

template <typename T>
bool kv_comparer(T* a, T* b)
{
	return generic_comparer(a->getText(), b->getText());
}

#endif