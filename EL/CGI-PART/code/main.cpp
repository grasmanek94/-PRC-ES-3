#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
																									   
#include <mqueue.h>     																	
#include <errno.h>      																	
#include <fcntl.h>      																	
#include <stdio.h>																			
			
//dit in de cgi app
mqd_t cgi_mq_open(mq_attr* obuf)
{																							
	mqd_t mqd;           /* queue descriptor */												
			
	mqd = mq_open("xbox_web_controller_app", O_RDONLY);																
	if (-1 != mqd)																			
	{																						
		if (!mq_getattr(mqd, obuf))														
		{																					
			printf("flags: 0x%x  maxmsg: %d  msgsize: %d  curmsgs: %d\n",					
				obuf->mq_flags, obuf->mq_maxmsg, obuf->mq_msgsize, obuf->mq_curmsgs);			
		}																					
		else
		{
			mq_close(mqd);
			mqd = -1;
			perror("mq_getattr()");
		}
	}																						
	else
	{
		perror("mq_open()");
	}

	return mqd;
}	

//dit komt in de daemon
mqd_t cgi_mq_create(int mq_flags, int mq_maxmsg, int mq_msgsize)
{
	mqd_t mqd;           /* queue descriptor */
	mq_attr obuf;
	obuf.mq_flags = mq_flags;
	obuf.mq_maxmsg = mq_maxmsg;
	obuf.mq_msgsize = mq_msgsize;
	obuf.mq_curmsgs = 0;

	unlink("/dev/mqueue/xbox_web_controller_app");
	mqd = mq_open("xbox_web_controller_app", O_CREAT | O_EXCL | O_RDWR, 0777, &obuf);
	if (-1 == mqd)
	{
		perror("mq_open()");
	}

	return mqd;
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

//in daemon
int* cgi_shm_create(int& shm_fd)
{
	unlink("/dev/shm/xbox_web_controller_app");
	shm_fd = shm_open("xbox_web_controller_app", O_CREAT | O_EXCL | O_RDWR, 0777);
	if (shm_fd == -1)
	{
		return NULL;
	}

	const size_t data_size = sizeof(int) * 21;
	int rtnval = ftruncate(shm_fd, data_size);
	if (rtnval != 0)
	{
		return NULL;
	}

	int* shm_addr = (int*)mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_addr == MAP_FAILED)
	{
		return NULL;
	}

	return (shm_addr);
}

//in cgi app
int* cgi_shm_open(int& shm_fd)
{
	shm_fd = shm_open("xbox_web_controller_app", O_RDWR, 0777);
	if (shm_fd == -1)
	{
		return NULL;
	}

	size_t size = lseek(shm_fd, 0, SEEK_END);

	int* shm_addr = (int*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_addr == MAP_FAILED)
	{
		return NULL;
	}

	return (shm_addr);
}

enum Actions
{
	ACTION_RUMBLE,															
	ACTION_LED																
};																			
																			
struct queue_message														
{																			
	int action;																
	int value;																
};																			

int main()
{																			
	std::cout																
		<< "Content-type: text/html" << std::endl							
		<< "Connection: close" << std::endl									
		<< std::endl;														
																			
	char *formdata = getenv("QUERY_STRING");								
	if (formdata == NULL)													
	{																		
		/* no data retrieved */												
		std::cout << "ERROR: BAD REQUEST" << std::endl;						
		return 0;															
	}

	std::vector<std::string> request_args;
	split(std::string(formdata), '&', request_args);
		
	if (request_args.size() < 1)
	{
		std::cout << "ERROR: HOW THE FUCK IS THIS EVEN POSSIBLE? Cosmic rays bombarding the processor and memory?" << std::endl;
		return 0;
	}


	return 0;
}
