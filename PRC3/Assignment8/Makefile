empty:=

#######################################################################################################
CFLAGS_RELEASE=-O3 -ggdb3
CFLAGS_DEBUG=-O0 -ggdb3 -Wall
CFLAGS_COMBINED_RELEASE=$(CFLAGS_RELEASE) $(CFLAGS)
CFLAGS_COMBINED_DEBUG=$(CFLAGS_DEBUG) $(CFLAGS)
SUFFIX_RELEASE=_REL
SUFFIX_DEBUG=_DBG

SUFFIX_SELECTED=
CFLAGS_SELECTED=

#######################################################################################################
CFLAGS_STATIC_LIBRARY=		-c
CFLAGS_INCLUDE_DIRS=		-I.
CFLAGS_COMMON=				-std=c++98 $(CFLAGS_INCLUDE_DIRS) $(CFLAGS_SELECTED)

#######################################################################################################
DEFAULT_CLEARER=
GPP=						g++
ARCHIVE=					ar rvs

#######################################################################################################
COMMON_INCLUDES=			
COMMON_DEFINITIONS=
MAIN_BASE_DIR=				./build

#######################################################################################################
COMMON_LIBRARIES=			-lpthread \
							-ldl \
							-lrt

#######################################################################################################
INCLUDE_DIRS_PROJECT=		-I./

PROJECT_NAME=				app

APP_PROJECT_LIBRARIES=		$(COMMON_LIBRARIES)
APP_PROJECT_INCLUDE_DIRS=	$(INCLUDE_DIRS_PROJECT)
APP_PROJECT_SOURCES=		$(shell find ./ ! -path "$(MAIN_BASE_DIR)/*" -name '*.c*')
APP_PROJECT_OBJ_DIR=		$(MAIN_BASE_DIR)/obj/$(PROJECT_NAME)/
APP_PROJECT_OBJECTS=		$(addprefix $(APP_PROJECT_OBJ_DIR),$(APP_PROJECT_SOURCES))
APP_PROJECT_EXECUTABLE=		$(MAIN_BASE_DIR)/$(PROJECT_NAME)$(SUFFIX_SELECTED).bin
APP_PROJECT_DEFINES=		$(COMMON_DEFINITIONS) \
							-DPROJECT_APP

AppProject: DEFAULT_CLEARER=$(APP_PROJECT_OBJ_DIR)
AppProject: COMMON_INCLUDES=$(APP_PROJECT_INCLUDE_DIRS)
AppProject: $(APP_PROJECT_OBJECTS)
	@$(GPP) $(CFLAGS_COMMON) $(CFLAGS_INCLUDE_DIRS) $(APP_PROJECT_INCLUDE_DIRS) $(addsuffix $(SUFFIX_SELECTED).o,$(addprefix ./,$^)) $(APP_PROJECT_LIBRARIES) -o $(APP_PROJECT_EXECUTABLE)

#######################################################################################################
all: r

.DEFAULT:
	@mkdir -p ./$(@D)
	@$(GPP) $(CFLAGS_COMMON) $(CFLAGS_STATIC_LIBRARY) $(CFLAGS_INCLUDE_DIRS) $(COMMON_INCLUDES) ./$(subst $(DEFAULT_CLEARER),$(empty),./$@) -o ./$@$(SUFFIX_SELECTED).o

clean:
	@rm -rf $(MAIN_BASE_DIR)/obj/*
	@rm -rf $(MAIN_BASE_DIR)/*.bin

d: SUFFIX_SELECTED=$(SUFFIX_DEBUG)
d: CFLAGS_SELECTED=$(CFLAGS_COMBINED_DEBUG)

r: SUFFIX_SELECTED=$(SUFFIX_RELEASE)
r: CFLAGS_SELECTED=$(CFLAGS_COMBINED_RELEASE)

d r: AppProject
	valgrind $(APP_PROJECT_EXECUTABLE)
