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
	mqd = mq_open("xbox_web_controller_app", O_RDWR, 0777, &obuf);
	if (-1 == mqd)
	{
		perror("mq_open()");
	}

	return mqd;
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
