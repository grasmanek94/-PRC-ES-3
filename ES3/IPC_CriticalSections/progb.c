#include <stdio.h>
#include <stdlib.h>
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
    
	while (shm_addr[0] != 'a')	//wacht totdat byte 0 in shm 'a' is
	{ }

	alphabet = (char*)malloc(size+1);
    for (int i = 0; i < size; i++) {
		alphabet[i] = shm_addr[i] + 'A' - 'a';
	}
	alphabet[size] = 0;

	printf("%s\n", alphabet);
	free(alphabet);

	shm_addr[0] += 'A' - 'a';	//maak van kleine letter 'a' hoofdletter 'A'
	return (0);					//stop
}
