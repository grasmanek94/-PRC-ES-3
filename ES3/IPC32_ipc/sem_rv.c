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

sem_t *     semdes[4];

void WaitForNumberWrite(int num)
{
	sem_wait(semdes[num]);
}

void PostNumberWrite(int num)
{
	sem_post(semdes[num]);
}

void CreateOrOpen()
{
	for (int i = 0; i < 4; ++i)
	{
		char name[10] = "1_process";
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

void WaitForOtherPrograms()
{
	WaitForNumberWrite(0);
	WaitForNumberWrite(1);
	WaitForNumberWrite(2);
	WaitForNumberWrite(3);
}

void StatementOneDone(int my_program_id)
{
	for (int i = 0; i < 4; ++i)
	{
		PostNumberWrite(my_program_id);
	}
}

void Done()
{
	for (int i = 0; i < 4; ++i)
	{
		char name[10] = "1_process";
		name[0] += i;//1_written 2_written etc

		sem_close(semdes[i]);
		sem_unlink(name);
	}
}

static int  shm_fd = -1;

static char *
my_shm_create(char * shm_name, int size)
{
	int     rtnval;
	char *  shm_addr;

	printf("Calling shm_open('%s')\n", shm_name);
	shm_fd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
	if (shm_fd == -1)
	{
		perror("ERROR: shm_open() failed");
		return NULL;
	}
	//printf("shm_open() returned %d\n", shm_fd);

	//printf("Calling ftrucate(%d,%d)\n", shm_fd, size);
	rtnval = ftruncate(shm_fd, size);
	if (rtnval != 0)
	{
		perror("ERROR: ftruncate() failed");
		return NULL;
	}
	//printf("ftruncate() returned %d\n", rtnval);

	//printf("Calling mmap(len=%d,fd=%d)\n", size, shm_fd);
	shm_addr = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_addr == MAP_FAILED)
	{
		perror("ERROR: mmap() failed");
		return NULL;
	}
	//printf("mmap() returned %p\n", shm_addr);

	return (shm_addr);
}

static char *
my_shm_open(char * shm_name)
{
	int     size;
	char *  shm_addr;

	//printf("Calling shm_open('%s')\n", shm_name);
	shm_fd = shm_open(shm_name, O_RDWR, 0600);
	if (shm_fd == -1)
	{
		perror("ERROR: shm_open() failed");
		return NULL;
	}
	//printf("shm_open() returned %d\n", shm_fd);

	//printf("Calling lseek(fd=%d,SEEK_END)\n", shm_fd);
	size = lseek(shm_fd, 0, SEEK_END);
	//printf("lseek() returned %d\n", size);

	//printf("Calling mmap(len=%d,fd=%d)\n", size, shm_fd);
	shm_addr = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_addr == MAP_FAILED)
	{
		perror("ERROR: mmap() failed");
		return NULL;
	}
	//printf("mmap() returned %p\n", shm_addr);

	return (shm_addr);
}

void statement_1()
{
	printf("[%d][1]\n", getpid());
	sleep(1);
}

void statement_2()
{
	printf("[%d][2]\n", getpid());
	sleep(1);
}


int main()
{
	CreateOrOpen();

	char* shm_name = "whichprogramcounter";
	char* program_id = my_shm_create(shm_name, sizeof(char));
	if (program_id == NULL)
	{
		program_id = my_shm_open(shm_name);
	}
	else
	{
		*program_id = 0;
	}

	if (program_id == NULL)
	{
		return 0;
	}

	char my_program_id = *program_id;
	++*program_id;

	while (true)
	{
		statement_1();

		StatementOneDone(my_program_id);
		WaitForOtherPrograms();

		statement_2();
	}

	//we go forever round 'n round 'n round so we never go round to this
	//Done();
	return (0);
}
