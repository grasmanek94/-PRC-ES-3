#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

#include "MergeSort.h"

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
		ckey->setValuePtr(MergeSort::Sort(ckey->getValuePtr()));
		ckey = ckey->getNext();
	}
	new_head = MergeSort::Sort(head);

	f.saveFile(*new_head, "sorted.bin");

	delete new_head;

	return 0;
}