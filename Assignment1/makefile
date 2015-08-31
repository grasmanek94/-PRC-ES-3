comma:= ,
empty:=
space:= $(empty) $(empty)

CYGWIN_BASE=/cygdrive/$(subst \,/,$(subst :,$(empty),$(CYGWIN64)))
PRC22LIBS=$(CYGWIN_BASE)/prc31libs

mkfile_path := $(subst $(space),$(empty),$(abspath $(lastword $(MAKEFILE_LIST))))
project_name := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

CFLAGS=-Wall -Werror -pedantic -ggdb -O0 -std=c++98 -Iproduct
CFLAGS_NORMAL=$(CFLAGS) -Iproduct/cars
CFLAGS_MOCK=$(CFLAGS) -Itest

RENTALADMIN=RentalAdministration.cpp
RENTALADMIN_SOURCE=product/$(RENTALADMIN)
RENTALADMIN_TESTSOURCE=product/$(RENTALADMIN)

CAR_SOURCE=product/cars/Car.cpp
SEDAN_SOURCE=product/cars/Sedan.cpp
LIMOUSINE_SOURCE=product/cars/Limousine.cpp

MAIN_SOURCES=product/main.cpp \
             $(RENTALADMIN_SOURCE) \
             $(CAR_SOURCE) \
             $(SEDAN_SOURCE) \
             $(LIMOUSINE_SOURCE)

SEDANTEST_SOURCES=test/SedanTest.cpp \
             $(CAR_SOURCE) \
             $(SEDAN_SOURCE)

LIMOUSINETEST_SOURCES=test/LimousineTest.cpp \
             $(CAR_SOURCE) \
             $(LIMOUSINE_SOURCE)

RENTALADMINTEST_SOURCE=test/RentalAdministrationTest.cpp \
             $(RENTALADMIN_TESTSOURCE)

#TEST_LIBS=-lgtest -lgtest_main -lpthread
TEST_LIBS=-lgtest -lgmock -lgmock_main -lpthread

GCC=g++

.phony: all clean sedan limousine admin

all: CarRental

CarRental: $(MAIN_SOURCES) Makefile product/*.h product/cars/*.h
	@$(GCC) $(CFLAGS_NORMAL) $(MAIN_SOURCES) -o $@

SedanTest: $(SEDANTEST_SOURCES) Makefile product/*.h product/cars/*.h
	@$(GCC) $(CFLAGS_NORMAL) $(SEDANTEST_SOURCES) $(TEST_LIBS) -o $@

LimousineTest: $(LIMOUSINETEST_SOURCES) Makefile product/*.h product/cars/*.h
	@$(GCC) $(CFLAGS_NORMAL) $(LIMOUSINETEST_SOURCES) $(TEST_LIBS) -o $@

RentalAdministrationTest: $(RENTALADMINTEST_SOURCE) Makefile product/*.h test/*.h
	$(GCC) $(CFLAGS_MOCK) $(RENTALADMINTEST_SOURCE) $(TEST_LIBS) -o $@

# $(RENTALADMIN_TESTSOURCE): $(RENTALADMIN_SOURCE)
# 	@ln -s ../$(RENTALADMIN_SOURCE) $(RENTALADMIN_TESTSOURCE)
# 	@ln -s ../$(RENTALADMIN_SOURCE:.cpp=.h) $(RENTALADMIN_TESTSOURCE:.cpp=.h)
# 	@ln -s ../$(RENTALADMIN_SOURCE:.cpp=.hpp) $(RENTALADMIN_TESTSOURCE:.cpp=.hpp)
# 	@ln -s ../$(RENTALADMIN_SOURCE:.cxx=.hxx) $(RENTALADMIN_TESTSOURCE:.cxx=.hxx)

clean:
	@rm -rf CarRental SedanTest LimousineTest RentalAdministrationTest test/RentalAdministration.cpp test/RentalAdministration.h

sedan: SedanTest
	@./SedanTest

limousine: LimousineTest
	@./LimousineTest

admin: RentalAdministrationTest
	@./RentalAdministrationTest
