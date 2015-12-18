#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "shared_data.hxx"

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

std::map<std::string, std::vector<std::string>> ParseUrlGetData(const std::vector<std::string>& gets)
{
	std::map<std::string, std::vector<std::string>> k_v;

	for (auto& i : gets)
	{
		std::string key;
		std::string value;
		size_t positionOfEquals = i.find("=");
		key = i.substr(0, positionOfEquals);
		if (positionOfEquals != std::string::npos)
		{
			value = i.substr(positionOfEquals + 1);
		}
		k_v[key].push_back(value);
	}
	return k_v;
}

int main()
{			
	int shm_fd;
	InputReport* report = cgi_shm_create(shm_fd);
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
		std::cout << "ERROR: HOW THE HELL IS THIS EVEN POSSIBLE? Cosmic rays bombarding the processor and memory?" << std::endl;
		return 0;
	}

	std::map<std::string, std::vector<std::string>> k_v = ParseUrlGetData(request_args);


	return 0;
}
