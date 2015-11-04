#include <stdio.h>
#include <stdlib.h>
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

sem_t* sem_e = SEM_FAILED;
sem_t* sem_s = SEM_FAILED;
sem_t* sem_n = SEM_FAILED;
sem_t* sem_pos = SEM_FAILED;
sem_t* sem_ctn = SEM_FAILED;

sem_t* PrepareSem(sem_t** sem, const char* name)
{
	*sem = sem_open(name, O_CREAT | O_EXCL, 0777, 1);

	if (*sem == SEM_FAILED)
	{
		*sem = sem_open(name, 0);

		if (*sem == SEM_FAILED)
		{
			perror("ERROR: sem_open() failed");
			printf("sem_open() returned %p\n", *sem);
		}
	}
	return *sem;
}

void CreateOrOpen()
{
	sem_t** semdes[3] = { &sem_e, &sem_s, &sem_n };

	for (int i = 0; i < 3; ++i)
	{
		char name[] = "0_consumer_producer";
		name[0] += i;
		PrepareSem(semdes[i], (const char*)name);
	}

#ifdef CONSUMER
	PrepareSem(&sem_pos, "pcp_position_consumer");
#else
	PrepareSem(&sem_pos, "pcp_position_producer");
	PrepareSem(&sem_ctn, "pcp_counter_producer");
#endif

}

void Done()
{
	sem_t** semdes[3] = { &sem_e, &sem_s, &sem_n };

	for (int i = 0; i < 3; ++i)
	{
		char name[] = "0_consumer_producer";
		name[0] += i;

		sem_close(*semdes[i]);
		sem_unlink(name);
	}

	sem_close(sem_pos);
#ifdef CONSUMER
	sem_unlink("pcp_position_consumer");
#else
	sem_unlink("pcp_position_producer");
	sem_unlink("pcp_counter_producer");
#endif

}

static char *
my_shm_open(const char * shm_name)
{
	int     size;
	char *  shm_addr;

	//printf("Calling shm_open('%s')\n", shm_name);
	int shm_fd = shm_open(shm_name, O_RDWR, 0600);
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

static char *
my_shm_create(const char * shm_name, int size)
{
	int     rtnval;
	char *  shm_addr;

	printf("Calling shm_open('%s')\n", shm_name);
	int shm_fd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
	if (shm_fd == -1)
	{
		return my_shm_open(shm_name);
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
	memset(shm_addr, 0, size);

	return (shm_addr);
}

unsigned long* circular_buffer;
const unsigned long circular_buffer_size = 4;
unsigned long* circular_buffer_position;
unsigned long* current_value;

void CreateCircularBuffer()
{
	circular_buffer = (unsigned long*)my_shm_create("shared_circular_buffer", sizeof(unsigned long)*circular_buffer_size);

#ifdef CONSUMER
	circular_buffer_position = (unsigned long*)my_shm_create("shared_consumer_position", sizeof(unsigned long));
	current_value = (unsigned long*)malloc(sizeof(unsigned long));
	*current_value = 0;
#else
	circular_buffer_position = (unsigned long*)my_shm_create("shared_producer_position", sizeof(unsigned long));
	current_value = (unsigned long*)my_shm_create("shared_producer_counter", sizeof(unsigned long));
#endif

}

void AdvanceBuffer()
{
	sem_wait(sem_pos);
	unsigned long val = (*circular_buffer_position + 1);
	(*circular_buffer_position) = val % circular_buffer_size;
	sem_post(sem_pos);
}

unsigned long GetCurrentBuffer(bool confirm_read)
{
	unsigned long val = circular_buffer[*circular_buffer_position];
	if (confirm_read)
	{
		circular_buffer[*circular_buffer_position] = 0;
	}
	return val;
}

void WriteCurrentBuffer(unsigned long number)
{
	circular_buffer[*circular_buffer_position] = number;
}

void take()
{
	unsigned long val = GetCurrentBuffer(true);
	if (val)
	{
		printf("%lu\n", val);
	}
	AdvanceBuffer();
}

void append()
{
	if (!GetCurrentBuffer(false))
	{
		WriteCurrentBuffer(++*current_value);
		AdvanceBuffer();
	}
}

void produce()
{
	usleep(1000 * (rand() % 3000));
}

void consume()
{
	usleep(1000 * (rand() % 3000));
}

void dostuff()
{
#ifdef CONSUMER
	sem_wait(sem_n);
	sem_wait(sem_s);
	take();
	sem_post(sem_s);
	sem_post(sem_e);
	consume();
#else
	produce();
	sem_wait(sem_e);
	sem_wait(sem_s);
	append();
	sem_post(sem_s);
	sem_post(sem_n);
#endif
}

int main()
{
	sysconf(_SC_ATEXIT_MAX);
	atexit(Done);

	CreateOrOpen();
	CreateCircularBuffer();

	while (true)
	{
		dostuff();
	}
	return (0);
}
