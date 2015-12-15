#include <cstdio>
#include "controllerinput.hxx"

ControllerInput::ControllerInput(libusb_device_handle *h, unsigned char endpointIn) {
	handle = h;
	epIn = endpointIn;

	static_assert (sizeof(InputReport) == 20, "InputReport size NOT 20 bytes, correct this!");
}

bool ControllerInput::Update() 
{
	int transferred = 0;
	libusb_interrupt_transfer(handle, epIn, (unsigned char*)&input, sizeof input, &transferred, 0);
	if (transferred != sizeof(input)) 
	{
		return false;
	}
	return true;
}

const InputReport ControllerInput::GetButtonStates() const
{
	return input;
}
