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

	head->addValue("ac_ik");
	head->addValue("ac_ben");
	head->addValue("ac_meneer");
	head->addValue("ac_rafal");
	head->addValue("ac_meneer");
	head->addValue("ac_ben");
	head->addValue("ac_ik");

	head->addValue("ab_ik");
	head->addValue("ab_ben");
	head->addValue("ab_meneer");
	head->addValue("ab_rafal");
	head->addValue("ab_meneer");
	head->addValue("ab_ben");
	head->addValue("ab_ik");
	//f.loadFile("data/gibberish.bin", *head);

	ckey = head;
	while (ckey)
	{
		ckey->setValuePtr(MergeSort::Sort(ckey->getValuePtr()));
		ckey = ckey->getNext();
	}
	new_head = MergeSort::Sort(head);

	new_head->print();

	f.saveFile(*new_head, "sorted.bin");

	delete new_head;

	return 0;
}