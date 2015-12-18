#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H
#include <libusb-1.0/libusb.h>

class ControllerInput 
{
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
