#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

#include "MergeSort.h"

//Sort  [ recursive multiple functions ] worst?
//Sort2 [ recursive one function ] meh..
//Sort3 [ nonrecursive ] seems to be the fastest on an i7-4710MQ
#define WHICH_SORT_TO_USE Sort3

int main()
{
	FileStructure f;
	Key* head = new Key();
	Key* ckey = NULL;
	Key* new_head = NULL;

	f.loadFile("data/gibberish.bin", *head);

	ckey = head;
	while (ckey)
	{
		ckey->setValuePtr(MergeSort::WHICH_SORT_TO_USE(ckey->getValuePtr()));
		ckey = ckey->getNext();
	}
	new_head = MergeSort::WHICH_SORT_TO_USE(head);

	f.saveFile(*new_head, "sorted.bin");

	delete new_head;

	return 0;
}