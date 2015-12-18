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


#include <libusb-1.0/libusb.h>

#include "controllerinput.hxx"
#include "controlleroutput.hxx"
#include "shared_data.hxx"
#include "sighandler.hxx"

const int vid = 0x045e;
const int pid = 0x028e;
const unsigned char endpointIN = 0x81;
const unsigned char endpointOUT = 0x01;

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
	install_sig_handler();

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
