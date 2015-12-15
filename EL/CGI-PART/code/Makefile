empty:=
#######################################################################################################
CFLAGS_COMMON=				-std=gnu++11 -I. -O0 -ggdb3 -Wall -Werror
#######################################################################################################
DEFAULT_CLEARER=	
CHOSEN_GPP=/el32/buildroot/output/host/usr/bin/arm-linux-g++
LIBS=-lrt
#######################################################################################################	
BUILD_DIR=				./build/
#######################################################################################################
RSP_SOURCES=				$(shell find ./ ! -path "./build/*" -name '*.c*')
RSP_OBJECTS=				$(addprefix $(BUILD_DIR),$(RSP_SOURCES))
RSP_EXECUTABLE=				main

RSP: $(RSP_OBJECTS)
	$(Q)$(CHOSEN_GPP) $(CFLAGS_COMMON) $(addsuffix _rsp.o,$(addprefix ./,$^)) $(LIBS) -o $(RSP_EXECUTABLE)

#######################################################################################################
all: RSP

.DEFAULT:
	@mkdir -p ./$(@D)
	$(CHOSEN_GPP) $(CFLAGS_COMMON) -c ./$(subst $(BUILD_DIR),$(empty),./$@) -o ./$@_rsp.o

clean:
	@rm -rf $(BUILD_DIR)*
