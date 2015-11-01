#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdbool.h>
#include <math.h>

sem_t *     semdes[8];

void WaitForNumberWrite(int num)
{
	sem_wait(semdes[num - 1]);
}

void PostNumberWrite(int num)
{
	sem_post(semdes[num - 1]);
}

void CreateOrOpen()
{
	for (int i = 0; i < 8; ++i)
	{
		char name[10] = "1_written";
		name[0] += i;//1_written 2_written etc

		semdes[i] = sem_open(name, O_CREAT | O_EXCL, 0777, 0);

		if (semdes[i] == SEM_FAILED)
		{
			semdes[i] = sem_open(name, 0);

			if (semdes[i] == SEM_FAILED)
			{
				perror("ERROR: sem_open() failed");
				printf("sem_open() returned %p\n", semdes[i]);
			}
		}
	}
}

void Done()
{
	for (int i = 0; i < 8; ++i)
	{
		char name[10] = "1_written";
		name[0] += i;//1_written 2_written etc

		sem_close(semdes[i]);
		sem_unlink(name);
	}
}

void count(int a, int b)
{
	if (a == 1)
	{
		printf("1\n");
	}
	else
	{
		WaitForNumberWrite(a - 1);
		printf("%d\n", a);
	}

	PostNumberWrite(a);
	WaitForNumberWrite(b-1);
	printf("%d\n", b);
	PostNumberWrite(b);
}

int programs[4][2] =
{
	{1, 5},
	{2, 6},
	{3, 7},
	{4, 8}
};

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Please supply A,B,C or D as second parameter to your command\n");
		return 0;
	}

	if (argv[1][0] < 'A' || argv[1][0] > 'D')
	{
		printf("Please supply A,B,C or D as second parameter to your command\n");
		return 0;
	}

	int program = argv[1][0] - 'A';
	int* vars = programs[program];

	CreateOrOpen();

	count(vars[0], vars[1]);

	Done();
	return (0);
}
