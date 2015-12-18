#include <cstdio>

#include "shared_data.hxx"

//in daemon
InputReport* cgi_shm_create(int& shm_fd)
{
	shm_unlink("xbox_web_controller_app");
	shm_fd = shm_open("xbox_web_controller_app", O_CREAT | O_EXCL | O_RDWR, 0777);
	if (shm_fd == -1)
	{
		return NULL;
	}

	const size_t data_size = sizeof(InputReport);
	int rtnval = ftruncate(shm_fd, data_size);
	if (rtnval != 0)
	{
		return NULL;
	}

	InputReport* shm_addr = (InputReport*)mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_addr == MAP_FAILED)
	{
		return NULL;
	}

	return (shm_addr);
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

	mq_unlink("xbox_web_controller_app");
	mqd = mq_open("xbox_web_controller_app", O_CREAT | O_EXCL | O_RDWR, 0777, &obuf);

	return mqd;
}

//dit in de cgi app
mqd_t cgi_mq_open(mq_attr* obuf)
{
	mqd_t mqd;           /* queue descriptor */

	mqd = mq_open("xbox_web_controller_app", O_RDONLY);
	if (-1 != mqd)
	{
		if (!mq_getattr(mqd, obuf))
		{
			//printf("flags: 0x%x  maxmsg: %d  msgsize: %d  curmsgs: %d\n",
			//	obuf->mq_flags, obuf->mq_maxmsg, obuf->mq_msgsize, obuf->mq_curmsgs);
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