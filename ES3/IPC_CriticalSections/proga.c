#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

typedef struct
{
	int prog_a_count;
	int prog_b_count;
} nice_print;

static int shm_fd = -1;
nice_print* shm_addr;
int rtnval = 0;
const char* shm_name = "ipc4";
int size = sizeof(nice_print);

int main(void) {
	stdout = freopen("/dev/tty1", "w", stdout);

    shm_fd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (shm_fd == -1) {
        perror ("ERROR: shm_open() failed");
    }
	rtnval = ftruncate(shm_fd, size);
	if (rtnval != 0) {
        perror ("ERROR: ftruncate() failed");
    }
    shm_addr = (nice_print *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED) {
        perror ("ERROR: mmap() failed");
    }
	memset(shm_addr, 0, size);
	
	printf("1\n");
	++shm_addr->prog_a_count;
	while (shm_addr->prog_b_count < 1) {}
	printf("3\n");
	++shm_addr->prog_a_count;
	while (shm_addr->prog_b_count < 2) {}
	printf("5\n");
	++shm_addr->prog_a_count;
	while (shm_addr->prog_b_count < 3) {}

	rtnval = close (shm_fd);
	if (rtnval != 0) {
		perror ("ERROR: close() failed");
	}
	
	rtnval = shm_unlink (shm_name);
	if (rtnval != 0) {
		perror ("ERROR: shm_unlink() failed");
	}
	return 0;
}

/*
process 0:							process 1:

while (true)						while (true)
{									{
	a_mon = true;					  	b_mon = true;
	b_ern = false;					  	a_ern = false;
	if (b_mon == true)				  	if (a_mon == true)
	{								  	{
		b_ern = true;				  		a_ern = true;
		a_mon = false;				  		b_mon = false;
	}								  	}
	while (b_ern || b_mon)			  	while (a_ern || a_mon)
	{								  	{
		a_mon = false;				  		b_mon = false;
		a_mon = true;				  		b_mon = true;
	}								  	}

	CriticalSection();				  	CriticalSection();

	a_mon = false;					  	b_mon = false;
	a_ern = false;					  	b_ern = false;
}									}
*/