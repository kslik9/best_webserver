#include "RequestData.hpp"

// void fillSeconPart(std::string &part_two, std::string &body, std::map<std::string, std::string> &headers)
// {
// 	if (headers["Content-Type"].find("multipart/form-data") != std::string::npos)
// 	{
// 		// std::cout << "------------------ multipart/form-data ------------------\n";
// 		// std::cout << "<";
// 		// std::cout << part_two;
// 		uploadfile(part_two);
// 		// std::cout << ">";
// 	}
// 	if (headers["Content-Type"].find("application/x-www-form-urlencoded") != std::string::npos)
// 	{
// 		// std::cout << "------------------ application/x-www-form-urlencoded ------------------\n";
// 	}
// 	if (headers["Content-Type"].find("text/plain") != std::string::npos)
// 	{
// 		// std::cout << "------------------ text/plain ------------------\n";
// 	}
// }

void	RequestData::split_parts(std::stringstream &iss)
{
	std::string line;
	bool trigger = false;
	while (1)
	{
		if(!std::getline(iss, line))
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

void fillFirstPart(std::string &part_one, std::string &method, std::string &target, std::string &httpVersion, std::map<std::string, std::string> &headers)
{
	int i = 0;
	std::string line;
	std::stringstream iss(part_one);
	while (1)
	{
		std::getline(iss, line);
		if (line.empty())
			break;
		if (i == 0)
		{
			std::stringstream fline(line);
			fline >> method >> target >> httpVersion;
		}
		else
		{
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

void	RequestData::parse_request(std::string &request,
				   std::string &method,
				   std::string &target,
				   std::string &httpVersion,
				   std::string &body,
				   std::map<std::string, std::string> &headers)
{
	// std::string part_one, part_two;
	std::stringstream iss(request);
	split_parts(iss);
	// std::cout << part_two << "\n";
	fillFirstPart(this->partOne, method, target, httpVersion, headers);
	// fillSeconPart(this->partTwo, body, headers);
}

RequestData::RequestData(std::string &request)
{
	parse_request(request, this->method, this->uri, this->httpVersion, this->body, this->headers);
}

std::string RequestData::getUri() const
{
	return this->uri;
}

std::string RequestData::getMethod() const
{
	return this->method;
}

std::string RequestData::getHttpVersion() const
{
	return this->httpVersion;
}

std::string RequestData::getBody() const
{
	return this->body;
}

std::map<std::string, std::string> RequestData::getHeaders() const
{
	return this->headers;
}

std::string RequestData::getAllHeaders() const
{
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

std::ostream &operator<<(std::ostream &o, RequestData const &i)
{
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
