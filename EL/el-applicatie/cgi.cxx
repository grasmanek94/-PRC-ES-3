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

InputReport* report = NULL;
int report_fd = -1;
mqd_t queue = -1;

bool prepare_key_access()
{
	InputReport* report = cgi_shm_open(report_fd);
	if (report)
	{
		return true;
	}

	std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: Cannot access shared memory\"\
	}\
}" << std::endl;

	return false;
}

bool prepare_queue_access()
{
	mq_attr attr;

	queue = cgi_mq_open(&attr);
	if (queue != -1)
	{
		return true;
	}

	std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: Cannot access message queue\"\
	}\
}" << std::endl;

	return false;
}

void handle_set_led(std::map<std::string, std::vector<std::string>>::iterator& set_led_found)
{
	if (!set_led_found->second.size())
	{
		std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: No LED ACTION specified\"\
	}\
}" << std::endl;
		return;
	}

	char action = (char)std::stoi(set_led_found->second[0]);
	if (action < MAX_LED_ACTIONS)
	{
		char message[message_size] = { ACTION_LED, action, 0 };
		if (mq_send(queue, message, message_size, 0) != 0)
		{
			int err = errno;
			std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: Cannot send message to daemon, error " << err << "\"\
	}\
}" << std::endl;
		}
		else
		{
			std::cout << "\
{\
	\"info\": {\
		\"success\" : true,\
		\"message\" : \"SUCCESS: Set LED ACTION to " << action << "\"\
	}\
}" << std::endl;
		}
	}
	else
	{
		std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: Invalid LED ACTION specified\"\
	}\
}" << std::endl;
	}
}

void handle_set_rumble(std::map<std::string, std::vector<std::string>>::iterator& set_rumble_found)
{
	if (!set_rumble_found->second.size())
	{
		std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: No SPEED specified\"\
	}\
}" << std::endl;
		return;
	}
	std::string i(set_rumble_found->second[0]);

	std::string key;
	std::string value;
	size_t positionOfEquals = i.find(":");
	key = i.substr(0, positionOfEquals);
	if (positionOfEquals != std::string::npos)
	{
		value = i.substr(positionOfEquals + 1);
	}

	unsigned char L = std::stoi(key);
	unsigned char B = std::stoi(value);

	unsigned char message[message_size] = { ACTION_RUMBLE, L, B };
	if (mq_send(queue, (char*)message, message_size, 0) != 0)
	{
		int err = errno;
		std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: Cannot send message to daemon, error " << err << "\"\
	}\
}" << std::endl;
	}
	else
	{
		std::cout << "\
{\
	\"info\": {\
		\"success\" : true,\
		\"message\" : \"SUCCESS: Set LED RUMBLE to " << (int)L << ":" << (int)B << "\"\
	}\
}" << std::endl;
	}
}

void output_current_keys()
{
	std::cout << "\
{\
	\"keys\": {\
		\"BTN_A\": " << (int)report->BTN_A << ",\
		\"BTN_B\": " << (int)report->BTN_B << ",\
		\"BTN_BACK\": " << (int)report->BTN_BACK << ",\
		\"BTN_LB\": " << (int)report->BTN_LB << ",\
		\"BTN_LOGO\": " << (int)report->BTN_LOGO << ",\
		\"BTN_RB\": " << (int)report->BTN_RB << ",\
		\"BTN_START\": " << (int)report->BTN_START << ",\
		\"BTN_STICK_LEFT\": " << (int)report->BTN_STICK_LEFT << ",\
		\"BTN_STICK_RIGHT\": " << (int)report->BTN_STICK_RIGHT << ",\
		\"BTN_X\": " << (int)report->BTN_X << ",\
		\"BTN_Y\": " << (int)report->BTN_Y << ",\
		\"DPAD_DOWN\": " << (int)report->DPAD_DOWN << ",\
		\"DPAD_LEFT\": " << (int)report->DPAD_LEFT << ",\
		\"DPAD_RIGHT\": " << (int)report->DPAD_RIGHT << ",\
		\"DPAD_UP\": " << (int)report->DPAD_UP << ",\
		\"STICK_LEFT_X\": " << (int)report->STICK_LEFT_X << ",\
		\"STICK_LEFT_Y\": " << (int)report->STICK_LEFT_Y << ",\
		\"STICK_RIGHT_X\": " << (int)report->STICK_RIGHT_X << ",\
		\"STICK_RIGHT_Y\": " << (int)report->STICK_RIGHT_Y << ",\
		\"TRIGGER_LEFT\": " << (int)report->TRIGGER_LEFT << ",\
		\"TRIGGER_RIGHT\": " << (int)report->TRIGGER_RIGHT << "\
	}\
}" << std::endl;
}

int main()
{			
	std::cout																
		<< "Content-type: text/html" << std::endl							
		<< "Connection: close" << std::endl									
		<< std::endl;														
		
	try
	{
		char *formdata = getenv("QUERY_STRING");
		if (formdata == NULL)
		{
			/* no data retrieved */
			std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: BAD REQUEST\"\
	}\
}" << std::endl;
			return 0;
		}

		std::vector<std::string> request_args;
		split(std::string(formdata), '&', request_args);

		if (request_args.size() < 1)
		{
			std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: HOW THE HELL IS THIS EVEN POSSIBLE? Cosmic rays bombarding the processor and memory?\"\
	}\
}" << std::endl;
			return 0;
		}

		std::map<std::string, std::vector<std::string>> k_v = ParseUrlGetData(request_args);

		auto set_led_found = k_v.find("l");
		if (set_led_found != k_v.end())
		{
			if (prepare_queue_access())
			{
				handle_set_led(set_led_found);
			}
			return 0;
		}

		auto set_rumble_found = k_v.find("r");
		if (set_rumble_found != k_v.end())
		{
			if (prepare_queue_access())
			{
				handle_set_rumble(set_rumble_found);
			}
			return 0;
		}

		auto get_keys_found = k_v.find("k");
		if (get_keys_found != k_v.end())
		{
			if (prepare_key_access())
			{
				output_current_keys();
			}
			return 0;
		}

		std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"ERROR: Unknown action\"\
	}\
}" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "\
{\
	\"info\": {\
		\"success\" : false,\
		\"message\" : \"EXCEPTION: " << e.what() << "\"\
	}\
}" << std::endl;
	}
	return 0;
}
