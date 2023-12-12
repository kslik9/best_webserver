#include "RequestData.hpp"

// std::string get_fileName(std::string part_two)
// {
// 	size_t k = part_two.find("filename=");

// 	size_t first = part_two.find("\"", k);
// 	size_t second = part_two.find("\"", first + 1);
// 	std::string tmp = part_two.substr(first + 1, second - first - 1);
// 	return tmp;

// 	// exit(0);
// }
// std::string get_content(std::string part_two)
// {
// 	size_t k = part_two.find("Content-Type");
// 	size_t start = part_two.find("\r\n", k);
// 	start = part_two.find("\r\n", start + 1);
// 	std::string tmp;

// 	size_t end = part_two.find("\r\n\r\n", start + 1);
// 	tmp = part_two.substr(start + 2, end - start - 1);
// 	std::cout << BLUE_TEXT << "start =" << start << " | end = " << end << std::endl
// 			  << RESET_COLOR;
// 	// exit(0);
// 	return tmp;
// }
// void uploadfile(std::string part_two)
// {
// 	// int how_many_sig()
// 	std::string filename, content;
// 	filename = "uploadedFiles/";
// 	filename = filename + get_fileName(part_two);
// 	std::cout << filename << std::endl;
// 	content = get_content(part_two);
// 	std::ofstream outputFile(filename);
// 	if (outputFile.is_open())
// 	{
// 		std::cout << "\nseccusefly\n";
// 		outputFile << content;
// 	}
// 	outputFile.close();
// }
// void fillSeconPart(std::string &part_two, std::string &body, std::map<std::string, std::string> &headers)
// {
// 	if (headers["Content-Type"].find("multipart/form-data") != std::string::npos)
// 	{
// 		// std::cout << "------------------ multipart/form-data ------------------\n";
// 		std::cout << "<";
// 		std::cout << part_two;
// 		// uploadfile(part_two);
// 		std::cout << ">";
// 	}
// 	if (headers["Content-Type"].find("application/x-www-form-urlencoded") != std::string::npos)
// 	{
// 		// std::cout << "------------------ application/x-www-form-urlencoded ------------------\n";
// 		body = part_two;
// 	}
// 	if (headers["Content-Type"].find("text/plain") != std::string::npos)
// 	{
// 		// std::cout << "------------------ text/plain ------------------\n";
// 		body = part_two;
// 	}
// }

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
		if (!trigger)
			this->partOne += line + "\n";
		else if (line != "\r")
			this->partTwo += line; //+ "\n";
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