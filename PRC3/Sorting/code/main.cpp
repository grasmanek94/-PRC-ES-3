#include <iostream>
#include <string>

#include <time.h>

#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

#include "BubbleSort.h"

int my_main()
{
    FileStructure f;
    Key* head = new Key();

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
	
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	Key* new_head =
		BubbleSort::PerformSortThreaded(head);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	std::cout << "Time: " << cpu_time_used << std::endl;
	delete new_head;
    return 0;
}

int inleveren_main()
{
	FileStructure f;
	Key* head = new Key();

	f.loadFile("data/gibberish.bin", *head);

	Key* new_head =
		BubbleSort::PerformSortThreaded(head);

	f.saveFile(*new_head, "sorted.bin");
	delete new_head;
	return 0;
}

int main()
{
	return my_main();
}