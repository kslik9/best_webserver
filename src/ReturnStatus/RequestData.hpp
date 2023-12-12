#pragma once
#include "webserv.hpp"

class RequestData
{
private:
    std::string target;
    std::string query_string;
    std::string method;
    std::string httpVersion;
    std::string body;
    std::string partOne;
    std::string partTwo;
    std::map<std::string, std::string> headers;
    void    parse_request(std::string &request);
    void    fillFirstPart();
    void    split_parts(std::stringstream &iss);
public:
    RequestData(std::string &request);
    // 
    std::string getUri() const;
    std::string getQueryString() const;
    std::string getMethod() const;
    std::string getHttpVersion() const;
    std::string getBody() const;
    std::map<std::string, std::string> getHeaders() const;
    std::string getAllHeaders() const;
    std::string getPartOne() const;
    std::string getPartTwo() const;
};

std::ostream &operator<<(std::ostream &o, RequestData const &i);
