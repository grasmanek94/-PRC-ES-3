#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

static int shm_fd = -1;
char* shm_addr;
int rtnval = 0;
int size = 26;
char* alphabet = "abcdefghijklmnopqrstuvwzyz";
char* shm_name = "ipc4";


int main(void) {
    shm_fd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (shm_fd == -1) {
        perror ("ERROR: shm_open() failed");
    }
	rtnval = ftruncate(shm_fd, size);
	if (rtnval != 0) {
        perror ("ERROR: ftruncate() failed");
    }
    shm_addr = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED) {
        perror ("ERROR: mmap() failed");
    }
	
	for (int i = 0; i < size; i++) {
		shm_addr[i] = alphabet[i];
	}
	
	while (shm_addr[0] != 'A') {
	}
	
	printf ("data (@ %#x): '%s'\n", shm_addr, shm_addr);
	
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
