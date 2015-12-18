#include <iostream>

int main()
{
	std::cout 
		<< "Content-type: text/html" << std::endl
		<< "Date: Thu, 01 Jan 1970 01:03:02 GMT" << std::endl
		<< "Connection: close" << std::endl
		<< std::endl
		<< "Hello CGI World" << std::endl;
	return 0;
}
