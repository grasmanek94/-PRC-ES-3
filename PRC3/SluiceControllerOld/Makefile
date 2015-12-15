CFLAGS=-Wall -Werror -ggdb -O3 -I./ -c -std=c++98
LDDFLAGS=-lrt -lpthread

MAIN_SOURCES=main.cpp
MAIN_OBJECTS=$(MAIN_SOURCES:.cpp=.o)

CC=g++

.phony: all clean

SluiceController: $(MAIN_OBJECTS) Makefile
	@$(CC) $(LDDFLAGS) $(MAIN_OBJECTS) -o $@
	
all: SluiceController

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf SluiceController *.o *.bin
