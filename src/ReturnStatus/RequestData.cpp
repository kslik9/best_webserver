#include "RequestData.hpp"

void parse_request(const std::string request, std::string &method, std::string &target, std::string &httpVersion, std::string &body, std::map<std::string, std::string> &headers)
{
	try
	{
		int i = 0;
		std::istringstream iss(request);
		// Parse request line
		// Parse headers
		std::string line;
		while (std::getline(iss, line) && line != "\r")
		{
			// std::cout << line << std::endl;
			if (i == 0)
			{
				std::stringstream liss(line);
				liss >> method >> target >> httpVersion;
			}
			else
			{
				size_t colonPos = line.find(':');
				if (colonPos != std::string::npos)
				{
					std::string key = line.substr(0, colonPos);
					std::string value = line.substr(colonPos + 1);
					value.erase(0, value.find_first_not_of(" \t"));
					headers[key] = value;
				}
			}
			++i;
		}
		// Parse body
		int posofrn = iss.str().find_last_of("\r\n");
		if (posofrn != std::string::npos)
		{
			std::cout << "founded!\n";
			body = iss.str().substr(posofrn);
		}
		// body = iss.str().substr(iss.tellg());
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		method = "GET";
		target = "/";
		httpVersion = "HTTP/1.1";
	}
}

RequestData::RequestData(std::string &request)
{
	parse_request(request, this->method, this->uri, this->httpVersion, this->body, this->headers);
	// this->headers["first"] = "second";
	// this->headers["first1"] = "second1";
	// this->headers["first2"] = "second2";
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
	o << "URI: " << i.getUri() << "\n"
	  << "Method: " << i.getMethod() << "\n"
	  << "httpVers: " << i.getHttpVersion() << "\n"
	  << "Headers: \n" << i.getAllHeaders() << "\n"
	  << "body: " << i.getBody();
	return o;
}
