#include <iostream>
#include <string>

#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

template <typename T>
inline bool generic_comparer(const T& a, const T& b)
{
	return a < b;
}

bool value_comparer(Value* a, Value* b)
{
	return generic_comparer(a->getText(), b->getText());
}

bool key_comparer(Key* a, Key* b)
{
	return generic_comparer(a->getText(), b->getText());
}

#include "QuickSort.h"
#include "BubbleSort.h"

Key* PerformQSort(Key* head)
{
	// sort all data
	// todo: your code here!
	Key* ckey = head;
	std::vector<Key*> keys;
	while (ckey)
	{
		//Add current key to keylist
		keys.push_back(ckey);

		//Get the values
		std::vector<Value*> values;
		Value* val = ckey->getValuePtr();
		while (val)
		{
			values.push_back(val);
			val = val->getNext();
		}

		//Sort values
		qSort(values, value_comparer);

		//Apply sorted values
		ckey->setValuePtr(values[0]);
		for (size_t i = 1; i < values.size(); ++i)
		{
			values[i - 1]->setNext(values[i]);
		}
		values[values.size() - 1]->setNext(NULL);

		//Go to next key (if any)
		ckey = ckey->getNext();
	}

	//sort the keys
	qSort(keys, key_comparer);

	//Apply sorted keys
	for (size_t i = 1; i < keys.size(); ++i)
	{
		keys[i - 1]->setNext(keys[i]);
	}
	keys[keys.size() - 1]->setNext(NULL);

	return keys[0];
}

Key* PerformBSort(Key* head)
{
	Key* ckey = head;
	while (ckey)
	{
		ckey->setValuePtr(BubbleSort2(ckey->getValuePtr()));
		//Go to next key (if any)
		ckey = ckey->getNext();
	}
	return BubbleSort2(head);
}

int main()
{
    FileStructure f;
    Key head;

    f.loadFile("data/gibberish.bin", head);
	/*
	head.addValue("ac_ik");
	head.addValue("ac_ben");
	head.addValue("ac_meneer");
	head.addValue("ac_rafal");
	head.addValue("ac_meneer");
	head.addValue("ac_ben");
	head.addValue("ac_ik");

	head.addValue("ab_ik");
	head.addValue("ab_ben");
	head.addValue("ab_meneer");
	head.addValue("ab_rafal");
	head.addValue("ab_meneer");
	head.addValue("ab_ben");
	head.addValue("ab_ik");
	*/
	Key* new_head = PerformBSort(&head);

	//new_head->print();
    f.saveFile(*new_head, "sorted.bin");

    return 0;
}