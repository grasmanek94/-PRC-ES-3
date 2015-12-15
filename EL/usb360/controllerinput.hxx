#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H
#include <string>
#include <libusb-1.0/libusb.h>

struct InputReport
{
	unsigned char messageType : 8;
	unsigned char packetSize : 8;
	bool DPAD_UP : 1;
	bool DPAD_DOWN : 1;
	bool DPAD_LEFT : 1;
	bool DPAD_RIGHT : 1;
	bool BTN_START : 1;
	bool BTN_BACK : 1;
	bool BTN_STICK_LEFT : 1;
	bool BTN_STICK_RIGHT : 1;
	bool BTN_LB : 1;
	bool BTN_RB : 1;
	bool BTN_LOGO : 1;
	bool UNUSED_00 : 1;
	bool BTN_A : 1;
	bool BTN_B : 1;
	bool BTN_X : 1;
	bool BTN_Y : 1;
	unsigned char TRIGGER_LEFT : 8;
	unsigned char TRIGGER_RIGHT : 8;
	short STICK_LEFT_X : 16;
	short STICK_LEFT_Y : 16;
	short STICK_RIGHT_X : 16;
	short STICK_RIGHT_Y : 16;
	int UNUSED_01 : 32;
	short UNUSED_02 : 16;
} __attribute__((packed));

class ControllerInput {
	public:
		ControllerInput(libusb_device_handle *h, unsigned char endpointIn);
		bool Update();
		const InputReport GetButtonStates() const;
	private:
		libusb_device_handle *handle;
		unsigned char epIn;
		InputReport input;
};

#endif
