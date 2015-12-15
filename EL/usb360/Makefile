CC = g++
CCARM = arm-linux-g++
LIBS = -lusb-1.0
CFLAGS = -O2 -Wall -Werror -std=gnu++11
SOURCES = main.cxx controllerinput.cxx controlleroutput.cxx

all: clean usb360-arm

usb360-arm:
	$(CCARM) $(CFLAGS) $(SOURCES) $(LIBS) -o $@


usb360-x86:
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $@
	

clean:
	rm -f usb360-*
