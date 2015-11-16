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

int main()
{
    FileStructure f;
    Key head;
    
    f.loadFile("data/gibberish.bin", head);

    // next line is only to show what kind of data we're working with
    // remove this line to increase performance!
    //head.print();
    
    // sort all data
    // todo: your code here!
	Key* ckey = &head;
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

	qSort(keys, key_comparer);

	for (size_t i = 1; i < keys.size(); ++i)
	{
		keys[i - 1]->setNext(keys[i]);
	}
	keys[keys.size() - 1]->setNext(NULL);

	//keys[0] is head
    // save sorted data into a new file called sorted.bin

    //f.saveFile(*keys[0], "sorted.bin");

    return 0;
}