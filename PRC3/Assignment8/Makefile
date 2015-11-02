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
#ofcourse google test won't compile somehow out of the box :(
CFLAGS_COMMON_TEST_LIB=		-std=gnu++11 $(CFLAGS_INCLUDE_DIRS) $(CFLAGS_SELECTED) 
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
GOOGLE_TEST_INCLUDE_DIRS=	-I./libraries/googletest -I./libraries/googletest/include
GOOGLE_TEST_SOURCES=		./libraries/__linux__/google_test.cc
GOOGLE_TEST_LIBRARY=		$(MAIN_BASE_DIR)/obj/google_test$(SUFFIX_SELECTED).o

GOOGLE_MOCK_INCLUDE_DIRS=	-I./libraries/googlemock -I./libraries/googlemock/include $(GOOGLE_TEST_INCLUDE_DIRS)
GOOGLE_MOCK_SOURCES=		./libraries/__linux__/google_mock.cc
GOOGLE_MOCK_LIBRARY=		$(MAIN_BASE_DIR)/obj/google_mock$(SUFFIX_SELECTED).o

GoogleTest: $(GOOGLE_TEST_SOURCES)
	@$(GPP) $(CFLAGS_COMMON_TEST_LIB) $(CFLAGS_STATIC_LIBRARY) $(GOOGLE_TEST_INCLUDE_DIRS) $(GOOGLE_TEST_SOURCES) -o $(GOOGLE_TEST_LIBRARY)
	
GoogleMock: $(GOOGLE_MOCK_SOURCES)
	@$(GPP) $(CFLAGS_COMMON_TEST_LIB) $(CFLAGS_STATIC_LIBRARY) $(GOOGLE_MOCK_INCLUDE_DIRS) $(GOOGLE_MOCK_SOURCES) -o $(GOOGLE_MOCK_LIBRARY)

#######################################################################################################
COMMON_LIBRARIES=			\
							-lpthread \
							-ldl \
							-lrt

#######################################################################################################
INCLUDE_DIRS_PROJECT=		\
							-I./app \
							-I./common

PROJECT_NAME=				app

LIBPROJECT_INCLUDE_DIRS=	$(INCLUDE_DIRS_PROJECT)
LIBPROJECT_SOURCES=			$(shell find ./common/ -name '*.c*')
LIBPROJECT_OBJ_DIR=			$(MAIN_BASE_DIR)/lib$(PROJECT_NAME)/
LIBPROJECT_OBJECTS=			$(addprefix $(LIBPROJECT_OBJ_DIR),$(LIBPROJECT_SOURCES))
LIBPROJECT_LIBRARY=			$(MAIN_BASE_DIR)/lib$(PROJECT_NAME)$(SUFFIX_SELECTED).a
LIBPROJECT_DEFINES=			$(COMMON_DEFINITIONS)

APP_PROJECT_LIBRARIES=		$(COMMON_LIBRARIES) \
							$(LIBPROJECT_LIBRARY) 
APP_PROJECT_INCLUDE_DIRS=	$(INCLUDE_DIRS_PROJECT)
APP_PROJECT_SOURCES=		$(shell find ./$(PROJECT_NAME)/ -name '*.c*')
APP_PROJECT_OBJ_DIR=		$(MAIN_BASE_DIR)/obj/$(PROJECT_NAME)/
APP_PROJECT_OBJECTS=		$(addprefix $(APP_PROJECT_OBJ_DIR),$(APP_PROJECT_SOURCES))
APP_PROJECT_EXECUTABLE=		$(MAIN_BASE_DIR)/$(PROJECT_NAME)$(SUFFIX_SELECTED).bin
APP_PROJECT_DEFINES=		$(COMMON_DEFINITIONS) \
							-DPROJECT_APP

LibProject: DEFAULT_CLEARER=$(LIBPROJECT_OBJ_DIR)
LibProject: COMMON_INCLUDES=$(LIBPROJECT_INCLUDE_DIRS)
LibProject: $(LIBPROJECT_OBJECTS)
	@$(ARCHIVE) $(LIBPROJECT_LIBRARY) $(addsuffix $(SUFFIX_SELECTED).o,$(addprefix ./,$^)) > /dev/null

AppProject: DEFAULT_CLEARER=$(APP_PROJECT_OBJ_DIR)
AppProject: COMMON_INCLUDES=$(APP_PROJECT_INCLUDE_DIRS)
AppProject: $(APP_PROJECT_OBJECTS)
	@$(GPP) $(CFLAGS_COMMON) $(CFLAGS_INCLUDE_DIRS) $(APP_PROJECT_INCLUDE_DIRS) $(addsuffix $(SUFFIX_SELECTED).o,$(addprefix ./,$^)) $(APP_PROJECT_LIBRARIES) -o $(APP_PROJECT_EXECUTABLE)

#######################################################################################################
TEST_INCLUDE_DIRS=			$(INCLUDE_DIRS_PROJECT) \
							$(GOOGLE_TEST_INCLUDE_DIRS) \
							$(GOOGLE_MOCK_INCLUDE_DIRS)
TEST_SOURCES=				$(shell find ./test/ -name '*.c*')
TEST_OBJ_DIR=				$(MAIN_BASE_DIR)/obj/test/
TEST_OBJECTS=				$(addprefix $(TEST_OBJ_DIR), $(TEST_SOURCES))
TEST_EXECUTABLE=			$(MAIN_BASE_DIR)/test$(SUFFIX_SELECTED).bin
TEST_DEFINES=				$(COMMON_DEFINITIONS) \
							-DUNIT_TESTING_FRAMEWORK
TEST_LIBRARIES=				$(COMMON_LIBRARIES) \
							$(LIBPROJECT_LIBRARY) \
							$(GOOGLE_TEST_LIBRARY) \
							$(GOOGLE_MOCK_LIBRARY)

TestProject: DEFAULT_CLEARER=$(TEST_OBJ_DIR)
TestProject: COMMON_INCLUDES=$(TEST_INCLUDE_DIRS)
TestProject: $(TEST_OBJECTS)
	@$(GPP) $(CFLAGS_COMMON) $(CFLAGS_INCLUDE_DIRS) $(TEST_INCLUDE_DIRS) $(addsuffix $(SUFFIX_SELECTED).o,$(addprefix ./,$^)) $(TEST_LIBRARIES) -o $(TEST_EXECUTABLE)

#######################################################################################################
all: r tr

.DEFAULT:
	@mkdir -p ./$(@D)
	@$(GPP) $(CFLAGS_COMMON) $(CFLAGS_STATIC_LIBRARY) $(CFLAGS_INCLUDE_DIRS) $(COMMON_INCLUDES) ./$(subst $(DEFAULT_CLEARER),$(empty),./$@) -o ./$@$(SUFFIX_SELECTED).o

clean:
	@rm -rf $(MAIN_BASE_DIR)/obj/*
	@rm -rf $(MAIN_BASE_DIR)/*.bin

d td: SUFFIX_SELECTED=$(SUFFIX_DEBUG)
d td: CFLAGS_SELECTED=$(CFLAGS_COMBINED_DEBUG)

r tr: SUFFIX_SELECTED=$(SUFFIX_RELEASE)
r tr: CFLAGS_SELECTED=$(CFLAGS_COMBINED_RELEASE)

d r: LibProject AppProject

td tr: GoogleTest GoogleMock LibProject TestProject
	valgrind $(TEST_EXECUTABLE)
