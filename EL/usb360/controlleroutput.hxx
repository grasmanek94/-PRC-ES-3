#ifndef CONTROLLEROUTPUT_H
#define CONTROLLEROUTPUT_H

#include <libusb-1.0/libusb.h>
#include <vector>

enum LED_ACTION
{
	LED_OFF,
	LED_ALL_BLINKING,
	LED_FLASH_1,
	LED_FLASH_2,
	LED_FLASH_3,
	LED_FLASH_4,
	LED_ON_1,
	LED_ON_2,
	LED_ON_3,
	LED_ON_4,
	LED_ROTATING,
	LED_BLINKING,
	LED_SLOW_BLINKING,
	LED_ALTERNATING,
};

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
