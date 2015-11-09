WD = D/Development/-PRC-ES-3/PRC3/Assignment8/peach
SB = gtest_main
SE = .cpp
EX = 
EL = pthread

CC = g++
FILES = $(wildcard *$(SE))
OBJS = $(FILES:$(SE)=.o)
LIBS = $(addprefix -l,$(EL)) -L.
COPT = -I. -Wall -O2 -x c++
SRC = $(SB)$(SE)
EXE = $(SB)

.SUFFIXES: .o $(SE)

$(EXE):	$(OBJS)
	rm -rf "${EXE}"
	$(CC) -o $(EXE) $(OBJS) $(LIBS)
	test -e "$(EXE)"

$(SE).o:
	$(CC) $(COPT) -c $< -o $@