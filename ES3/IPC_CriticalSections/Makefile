#
#	Makefile for IPC32
#
#	(c) Fontys 2010, Joris Geurts
#

BINARIES = proga progb shm

#CC = i586-linux-g++
CC = gcc
CFLAGS = -g3 -Wall -W -Wshadow -Wcast-qual -Wwrite-strings -std=c99 -D_XOPEN_SOURCE=500
LDLIBS = -lrt -lpthread

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

proga: proga.o

progb: progb.o

shm: shm.o
