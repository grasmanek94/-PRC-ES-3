#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

static int  shm_fd = -1;
char* shm_addr;
int rtnval = 0;
int size;
char* alphabet;
const char* shm_name = "ipc4";

int main(void)
{
    shm_fd = shm_open (shm_name, O_RDWR, 0600);
    if (shm_fd == -1) {
        perror ("ERROR: shm_open() failed");
    }
    
    size = lseek (shm_fd, 0, SEEK_END);
    shm_addr = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED) {
        perror ("ERROR: mmap() failed");
    }
    
    for (int i = 0; i < size; i++) {
		alphabet[i] = shm_addr[i]+32;
	}
	
	printf("%s\n", alphabet);
    
	return (0);
}
