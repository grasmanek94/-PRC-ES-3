#include "FileStructure.h"
#include "Value.h"
#include "Key.h"

#include "MergeSort.h"

//Sort  [ recursive multiple functions ] worst?
//Sort2 [ recursive one function ] seems to be the fastest on an i7-4710MQ with both -O0 and -O3
//Sort3 [ nonrecursive ] meh...
#define WHICH_SORT_TO_USE Sort2

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