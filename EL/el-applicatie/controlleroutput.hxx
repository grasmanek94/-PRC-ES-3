#ifndef CONTROLLEROUTPUT_H
#define CONTROLLEROUTPUT_H

#include <libusb-1.0/libusb.h>
#include <vector>

#include "shared_data.hxx"

class ControllerOutput
{
	public:
		ControllerOutput(libusb_device_handle *h, unsigned char endpointOut);
		void SetRumble(unsigned char speedB, unsigned char speedL);
		void SetLeds(LED_ACTION ledPattern);
	
	private:
		libusb_device_handle *handle;
		unsigned char epOut;
		void sendData(const std::vector<unsigned char>& data);
};

#endif
