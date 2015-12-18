#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}										

int main()
{																			
	std::cout																
		<< "Content-type: text/html" << std::endl							
		<< "Connection: close" << std::endl									
		<< std::endl;														
																			
	char *formdata = getenv("QUERY_STRING");								
	if (formdata == NULL)													
	{																		
		/* no data retrieved */												
		std::cout << "ERROR: BAD REQUEST" << std::endl;						
		return 0;															
	}

	std::vector<std::string> request_args;
	split(std::string(formdata), '&', request_args);
		
	if (request_args.size() < 1)
	{
		std::cout << "ERROR: HOW THE FUCK IS THIS EVEN POSSIBLE? Cosmic rays bombarding the processor and memory?" << std::endl;
		return 0;
	}


	return 0;
}
