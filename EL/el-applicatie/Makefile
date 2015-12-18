#######################################################################################
CXX=g++
CXXARM=arm-linux-g++
#######################################################################################
CXXFLAGS=-O2 -Wall -Werror -std=gnu++11
#######################################################################################
LIBS_DAEMON=-lusb-1.0 -lrt
SOURCES_DAEMON=daemon.cxx controllerinput.cxx controlleroutput.cxx shared_data.cxx sighandler.cxx
OUT_DAEMON=x360_daemon
#######################################################################################
LIBS_CGI=-lrt
SOURCES_CGI=cgi.cxx shared_data.cxx
OUT_CGI=x360_cgi
#######################################################################################
all: clean arm
#######################################################################################
arm:
	$(CXXARM) $(CXXFLAGS) $(SOURCES_DAEMON) $(LIBS_DAEMON) -o $(OUT_DAEMON)
	$(CXXARM) $(CXXFLAGS) $(SOURCES_CGI) $(LIBS_CGI) -o $(OUT_CGI)
#	cp ./$(OUT_DAEMON) /bin/$(OUT_DAEMON)
#	cp ./$(OUT_CGI) /var/www/cgi-bin/$(OUT_CGI)
#	cp ./ais/S61$(OUT_DAEMON) /etc/init.d/S61$(OUT_DAEMON)
#	cp ./ais/S60httpd /etc/init.d/S60httpd
#######################################################################################
native:
	$(CXX) $(CXXFLAGS) $(SOURCES_DAEMON) $(LIBS_DAEMON) -o $(OUT_DAEMON)
	$(CXX) $(CXXFLAGS) $(SOURCES_CGI) $(LIBS_CGI) -o $(OUT_CGI)
#	cp ./$(OUT_DAEMON) /bin/$(OUT_DAEMON)
#	cp ./$(OUT_CGI) /var/www/cgi-bin/$(OUT_CGI)
#	cp ./ais/S61$(OUT_DAEMON) /etc/init.d/S61$(OUT_DAEMON)
#	cp ./ais/S60httpd /etc/init.d/S60httpd
#######################################################################################

clean:
	rm -f x360_daemon x360_cgi
