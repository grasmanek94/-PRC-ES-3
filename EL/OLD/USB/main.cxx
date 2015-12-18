//VS Intellisense libUSB fix
#ifdef _MSC_VER
#define __cplusplus
#undef _WIN64
#undef _WIN32
#undef _MSC_VER
#define __linux
#define __GNUC__ 6
#endif

#include <libusb-1.0/libusb.h>
int main()
{
	libusb_device_handle *h;
	unsigned char data[] = { 1, 3, 0x0a };
	int transferred;
	
	libusb_init(NULL);
	h = libusb_open_device_with_vid_pid(NULL, 0x045e, 0x028e);
	int e = libusb_interrupt_transfer(h, 0x02, data, sizeof data, &transferred, 0);

	return e;
}
