#include "RequestData.hpp"

void parse_request(const std::string &request, std::string &method, std::string &target) {
	try
	{
		std::istringstream iss(request);
		iss >> method >> target;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		method = "GET";
		target = "/";
	}
}

RequestData::RequestData(std::string &request) {
    parse_request(request, this->method, this->uri);
}

std::string RequestData::getUri() const {
    return this->uri;
}

std::string RequestData::getMethod() const {
    return this->method;
}