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

#include "controllerinput.hxx"
#include "controlleroutput.hxx"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <libusb-1.0/libusb.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string>

const int vid = 0x045e;
const int pid = 0x028e;
const unsigned char endpointIN = 0x81;
const unsigned char endpointOUT = 0x01;

static void handler(int sig, siginfo_t *si, void *unused)
{
    exit(0);
}

int main()
{
	struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
	if (sigaction(SIGSEGV, &sa, NULL) == -1)
	{
		std::cout << "Doennie" << std::endl;
	}

	int error = 0;

	libusb_context *context = NULL;
	libusb_device_handle *h = NULL;
	error = libusb_init(&context);

	if (error) 
	{
		std::cout << "Failed to initialize libusb: "
			<< libusb_error_name(error) << std::endl;
		return 1;
	}

	h = libusb_open_device_with_vid_pid(NULL, vid, pid);
	if (!h)
	{
		std::cout << "Failed to open device" << std::endl;
		return 1;
	}
	std::cout << "Opened Xbox 360 controller." << std::endl;

	
	ControllerInput* controls = new ControllerInput(h, endpointIN);
	ControllerOutput* output = new ControllerOutput(h, endpointOUT);

	output->SetLeds(LED_ALL_BLINKING);

	bool monitor = true;
	std::cout << "Monitoring" << std::endl;
	while (monitor) 
	{
		if (controls->Update())
		{
			std::cout << "\033[2J\033[1;1H";

			InputReport report = controls->GetButtonStates();

			std::cout << "LTrig: " << report.TRIGGER_LEFT << "     RTrig: " << report.TRIGGER_RIGHT << std::endl;
			std::cout << "LB: " << report.BTN_LB << "        RB: " << report.BTN_RB << std::endl;
			std::cout << "LX: " << report.STICK_LEFT_X << "     RX: " << report.STICK_RIGHT_X << std::endl;
			std::cout << "LY: " << report.STICK_LEFT_Y << "     RY: " << report.STICK_RIGHT_Y << std::endl;
			std::cout << "DU: " << report.DPAD_UP << "        Y: " << report.BTN_Y << std::endl;
			std::cout << "DD: " << report.DPAD_DOWN << "        X: " << report.BTN_X << std::endl;
			std::cout << "DL: " << report.DPAD_LEFT << "        B: " << report.BTN_B << std::endl;
			std::cout << "DR: " << report.DPAD_RIGHT << "        A: " << report.BTN_A << std::endl;
			std::cout << "Back: " << report.BTN_BACK << "     Start: " << report.BTN_START << std::endl;
			std::cout << "LJoy: " << report.BTN_STICK_LEFT << "     RJoy: " << report.BTN_STICK_RIGHT << std::endl;

			if (report.BTN_A) 
			{
				output->SetRumble(255,255);
			}
			else 
			{
				output->SetRumble(0,0);
			}

			if (report.DPAD_UP) {
				output->SetLeds(LED_ON_1);
			}

			if (report.DPAD_DOWN) {
				output->SetLeds(LED_ON_2);
			}

			if (report.DPAD_LEFT) {
				output->SetLeds(LED_ON_3);
			}

			if (report.DPAD_RIGHT) {
				output->SetLeds(LED_ON_4);
			}

			if (report.BTN_LOGO) {
				monitor = false;
			}
		}
	}

	usleep(100000);

	output->SetLeds(LED_OFF);
	
	usleep(100000);

	output->SetRumble(0, 0);
	
	usleep(100000);
	
	libusb_close(h);
	libusb_exit(context);

	std::cout << "Closing..." << std::endl;
	return 0;
}
