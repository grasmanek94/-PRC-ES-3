#
#	Makefile for IPC32
#
#	(c) Fontys 2010, Joris Geurts
#

BINARIES = sem shm thread mq fork dutycycle sem_mult sem_rv

#CC = i586-linux-g++
CC = gcc
CFLAGS = -g3 -Wall -W -Wshadow -Wcast-qual -Wwrite-strings -std=c99 -D_XOPEN_SOURCE=500
LDLIBS = -lrt -lpthread -lm

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

sem: sem.o
shm: shm.o
thread: thread.o
mq: mq.o
fork: fork.o
dutycycle: dutycycle.o
sem_mult: sem_mult.o
sem_rv: sem_rv.o
