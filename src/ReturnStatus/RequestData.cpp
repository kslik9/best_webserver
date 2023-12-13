#include "RequestData.hpp"

void RequestData::split_parts(std::stringstream &iss)
{
	std::string line;
	bool trigger = false;
	while (1)
	{
		if (!std::getline(iss, line))
			break;
		if (line == "\r" && !trigger)
			trigger = true;
		// ------------------------
		if (trigger)
			this->partTwo += line + "\n";
		else
			this->partOne += line + "\n";
	}
}

void	RequestData::fillFirstPart()
{
	int i = 0;
	std::string line;
	std::stringstream iss(this->partOne);
	while (1) {
		std::getline(iss, line);
		if (line.empty())
			break;
		if (i == 0) {
			std::stringstream fline(line);
			fline >> this->method >> this->target >> this->httpVersion;
			int pos = target.find("?");
			if (pos != std::string::npos)
			{
				query_string = target.substr(pos + 1);
				target = target.substr(0, pos);
			}
		}
		else {
			std::istringstream s_iss(line);
			std::string key, value;
			std::getline(s_iss, key, ':');
			std::getline(s_iss, value);
			size_t start = value.find_first_not_of(" \t");
			value = value.substr(start);
			headers[key] = value;
		}
		i++;
	}
}

void	RequestData::parse_request(std::string &request)
{
	// std::cout << "------------- RAW -------------\n";
	// std::cout << request << std::endl;
	// std::cout << "------------- --- -------------\n";
	// std::string part_one, part_two;
	std::stringstream iss(request);
	split_parts(iss);
	fillFirstPart();
	// fillSeconPart(part_two, body, headers);
}

RequestData::RequestData(std::string &request) {
	parse_request(request);
}

RequestData::~RequestData() {
	this->headers.clear();
}

std::string RequestData::getUri() const {
	return this->target;
}

std::string RequestData::getMethod() const {
	return this->method;
}

std::string RequestData::getHttpVersion() const {
	return this->httpVersion;
}

std::string RequestData::getBody() const {
	return this->body;
}

std::map<std::string, std::string> RequestData::getHeaders() const {
	return this->headers;
}

std::string RequestData::getQueryString() const {
	return this->query_string;
}

std::string RequestData::getAllHeaders() const {
	typedef std::map<std::string, std::string>::const_iterator iterator;
	std::string holyders;
	iterator it = this->headers.begin();
	iterator it_end = this->headers.end();
	while (it != it_end)
	{
		holyders += (it->first + "=" + it->second).append("\n");
		++it;
	}
	return holyders;
}

std::ostream &operator<<(std::ostream &o, RequestData const &i) {
	o << "------------------------------------\n"
	  << "URI: " << i.getUri() << "\n"
	  << "Method: " << i.getMethod() << "\n"
	  << "httpVers: " << i.getHttpVersion() << "\n"
	  << "Headers: \n"
	  << i.getAllHeaders() << "\n"
	  << "body: " << i.getBody()
	  << "------------------------------------\n";
	return o;
}

std::string RequestData::getPartOne() const {
	return this->partOne;
}

std::string RequestData::getPartTwo() const {
	return this->partTwo;
}

void	RequestData::setBody(std::string &body) {
	this->body = body;
}