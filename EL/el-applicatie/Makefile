#######################################################################################
CXX = g++
CXXARM = arm-linux-g++
#######################################################################################
CXXFLAGS = -O2 -Wall -Werror -std=gnu++11
#######################################################################################
LIBS_DAEMON = -lusb-1.0 -lrt
SOURCES_DAEMON = daemon.cxx controllerinput.cxx controlleroutput.cxx shared_data.cxx sighandler.cxx
#######################################################################################
LIBS_CGI = -lrt
SOURCES_CGI = cgi.cxx shared_data.cxx
#######################################################################################
all: clean arm
#######################################################################################
arm:
	$(CXXARM) $(CXXFLAGS) $(SOURCES_DAEMON) $(LIBS_DAEMON) -o x360_daemon
	$(CXXARM) $(CXXFLAGS) $(SOURCES_CGI) $(LIBS_CGI) -o x360_cgi
#######################################################################################
native:
	$(CXX) $(CXXFLAGS) $(SOURCES_DAEMON) $(LIBS_DAEMON) -o x360_daemon
	$(CXX) $(CXXFLAGS) $(SOURCES_CGI) $(LIBS_CGI) -o x360_cgi
#######################################################################################

clean:
	rm -f x360_daemon x360_cgi
