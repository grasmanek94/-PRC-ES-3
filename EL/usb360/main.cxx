//VS Intellisense libUSB fix
#ifdef _MSC_VER
#define __cplusplus
#undef _WIN64
#undef _WIN32
#undef _MSC_VER
#define __linux
#define __GNUC__ 6
#define __attribute__(a)
#endif

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <mqueue.h>     																	
#include <errno.h>      																	
#include <fcntl.h>      																	
#include <sys/types.h>
#include <sys/stat.h>

#include <libusb-1.0/libusb.h>

#include "controllerinput.hxx"
#include "controlleroutput.hxx"

const int vid = 0x045e;
const int pid = 0x028e;
const unsigned char endpointIN = 0x81;
const unsigned char endpointOUT = 0x01;
const size_t message_size = 3;
const size_t message_amount = 16;

static void handler(int sig, siginfo_t *si, void *unused)
{
    exit(0);
}

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
	if (-1 == mqd)
	{
		perror("mq_open()");
	}

	return mqd;
}

enum Actions
{
	ACTION_LED,
	ACTION_RUMBLE
};

int main()
{
	/*
	turn into a
                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /           |  /                                                                                                                                                          */
     daemon    (     0       ,       0    );                                                                                                                                                                         /*
 \  \           | `._   `\\  |  //'   _,' |           /  /
  `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
     ``       /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |     /'\_\_\ | /_/_/`\     |   |
            \   \__, \_     `~'     _/ .__/   /
             `-._,-'   `-._______,-'   `-._,-'
*/
	struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
	if (sigaction(SIGSEGV, &sa, NULL) == -1)
	{
		std::cout << "Iets doet het niet maar oke we gaan wel door!" << std::endl;
	}

	int shm_fd;

	InputReport* report = cgi_shm_create(shm_fd);
	mqd_t queue = -1;
	if (!report)
	{
		std::cout << "Failed to create SHM" << std::endl;
		return 1;
	}

	queue = cgi_mq_create(O_NONBLOCK, message_amount, message_size);
	if (queue == -1)
	{
		close(shm_fd);
		std::cout << "Failed to create QUEUE" << std::endl;
		return 1;
	}

	int error = 0;

	libusb_context *context = NULL;
	libusb_device_handle *h = NULL;
	error = libusb_init(&context);

	if (error) 
	{
		close(shm_fd);
		mq_close(queue);
		std::cout << "Failed to initialize libusb: "
			<< libusb_error_name(error) << std::endl;
		return 1;
	}

	h = libusb_open_device_with_vid_pid(NULL, vid, pid);
	if (!h)
	{
		close(shm_fd);
		mq_close(queue);
		std::cout << "Failed to open device" << std::endl;
		return 1;
	}
	std::cout << "Opened Xbox 360 controller." << std::endl;

	
	ControllerInput* controls = new ControllerInput(h, endpointIN);
	ControllerOutput* output = new ControllerOutput(h, endpointOUT);

	output->SetLeds(LED_ALL_BLINKING);

	bool monitor = true;
	unsigned char message[message_size];
	while (monitor) 
	{
		usleep(1000);

		if (controls->Update())//new controller data?
		{
			*report = controls->GetButtonStates();
		}

		if (mq_receive(queue, (char*)message, message_size, NULL) != -1)
		{
			switch (message[0])
			{

			case ACTION_LED:
				output->SetLeds((LED_ACTION)message[1]);
				break;

			case ACTION_RUMBLE:
				output->SetRumble(message[1], message[2]);
				break;

			default://anything else, quit daemon
				monitor = false;
				std::cout << "Closing..." << std::endl;
				break;

			}
		}
	}

	output->SetLeds(LED_OFF);
	output->SetRumble(0, 0);
	
	usleep(100000);
	
	libusb_close(h);
	libusb_exit(context);

	close(shm_fd);
	mq_close(queue);

	return 0;
}
