#pragma once
#include "webserv.hpp"

class RequestData
{
private:
    std::string uri;
    std::string method;
    std::string httpVersion;
    std::map<std::string, std::string> headers;
    std::string body;

    std::string partOne;
    std::string partTwo;
    void split_parts(std::stringstream &iss);
    void parse_request(std::string &request,
				   std::string &method,
				   std::string &target,
				   std::string &httpVersion,
				   std::string &body,
				   std::map<std::string, std::string> &headers);

public:
    RequestData(std::string &request);
    // 
    std::string getUri() const;
    std::string getMethod() const;
    std::string getHttpVersion() const;
    std::string getBody() const;
    std::map<std::string, std::string> getHeaders() const;
    std::string getAllHeaders() const;
    std::string getPartOne() const;
    std::string getPartTwo() const;
};

std::ostream &operator<<(std::ostream &o, RequestData const &i);
