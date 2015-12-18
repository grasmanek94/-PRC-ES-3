#include <cstdio>
#include "controlleroutput.hxx"

ControllerOutput::ControllerOutput(libusb_device_handle *h, unsigned char endpointOut) 
{
	handle = h;
	epOut = endpointOut;
}

void ControllerOutput::sendData(const std::vector<unsigned char>& data)
{
	int transferred = 0;
	libusb_interrupt_transfer(handle, epOut, (unsigned char*)data.data(), data.size(), &transferred, 0);
	if ((size_t)transferred != data.size())
	{
		perror("Error while sending.");
	}
}

void ControllerOutput::SetRumble(unsigned char speedB, unsigned char speedL) 
{
	sendData(std::vector<unsigned char>({ 0x00, 0x08, 0x00, speedB, speedL, 0x00, 0x00, 0x00 }));
}

void ControllerOutput::SetLeds(LED_ACTION ledPattern)
{
	sendData(std::vector <unsigned char>({ 0x01, 0x03, (unsigned char)ledPattern }));
}
