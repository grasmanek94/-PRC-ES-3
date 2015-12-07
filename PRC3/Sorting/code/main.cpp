#include <iostream>
#include <string>

#include <time.h>

#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

#include "BubbleSort.h"
#include "MergeSort.h"

class TM
{
private:
	clock_t start;
	clock_t end;
	double cpu_time_used;
public:
	TM()
		: start(0), end(0), cpu_time_used(0.0)
	{ }

	void Start()
	{
		start = clock();
	}

	void Stop()
	{
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	}

	double Elapsed()
	{
		return cpu_time_used;
	}
};

TM timemeasure;

void TimeStartLoadFile(FileStructure* fs, const std::string& filename, Key* head)
{
	fs->loadFile(filename, *head);
	timemeasure.Start();
}

void SaveFile(FileStructure* fs, const std::string& filename, Key* head, bool print_time = false)
{
	timemeasure.Stop();
	if (print_time)
	{
		std::cout << "Time: " << timemeasure.Elapsed() << std::endl;
	}
	fs->saveFile(*head, filename);
}

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

	timemeasure.Start();
	Key* new_head =
		MergeSort::PerformSortThreaded(head);
	timemeasure.Stop();

	std::cout << "Time: " << timemeasure.Elapsed() << std::endl;

	new_head->print();

	delete new_head;
    return 0;
}

int inleveren_main()
{
	FileStructure f;
	Key* head = new Key();

	TimeStartLoadFile(&f, "data/gibberish.bin", head);

	Key* new_head =
		MergeSort::PerformSortThreaded(head);

	SaveFile(&f, "sorted.bin", new_head, true);

	delete new_head;
	return 0;
}

int main()
{
	int retval =
		//my_main();
		inleveren_main();
	return retval;
}