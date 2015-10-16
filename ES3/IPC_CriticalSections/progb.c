#include <stdio.h>
#include <stdlib.h>
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

static int  shm_fd = -1;
int rtnval = 0;
const char* shm_name = "ipc4";
nice_print* shm_addr;
int size = sizeof(nice_print);

int main(void)
{
	stdout = freopen("/dev/tty1", "w", stdout);

    shm_fd = shm_open (shm_name, O_RDWR, 0600);
    if (shm_fd == -1) {
        perror ("ERROR: shm_open() failed");
    }

    shm_addr = (nice_print *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED) {
        perror ("ERROR: mmap() failed");
    }
    
	while (shm_addr->prog_a_count < 1) {}
	printf("2\n");
	++shm_addr->prog_b_count;
	while (shm_addr->prog_a_count < 2) {}
	printf("4\n");
	++shm_addr->prog_b_count;
	while (shm_addr->prog_a_count < 3) {}
	printf("6\n");
	++shm_addr->prog_b_count;

	return (0);					//stop
}
