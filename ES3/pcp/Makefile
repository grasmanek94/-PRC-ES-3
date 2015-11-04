BINARIES = producer consumer

CC = gcc
CFLAGS = -g3 -Wall -W -Wshadow -Wcast-qual -Wwrite-strings -std=c99 -D_XOPEN_SOURCE=500
LDLIBS = -lrt -lpthread -lm

all:	$(BINARIES)

clean:
	rm *.o $(BINARIES)

producer: producer.o
consumer: consumer.o
