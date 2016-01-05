CFLAGS=-Wall -Werror -ggdb -O0 -Icode -c
LDDFLAGS=

MAIN_SOURCES=code/main.cpp
MAIN_OBJECTS=$(MAIN_SOURCES:.cpp=.o) \
			 objects/FileStructure.o \
			 objects/Key.o \
			 objects/Value.o

TEST_LIBS=-lgtest -lgtest_main -lpthread

CC=g++

.phony: all clean

sort: $(MAIN_OBJECTS) Makefile code/FileStructure.h
	@$(CC) $(LDDFLAGS) $(MAIN_OBJECTS) -o $@
	
all: sort

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf sort code/*.o test/*.o *.bin
