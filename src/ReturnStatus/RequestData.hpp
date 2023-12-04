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

public:
    RequestData(std::string &request);
    // 
    std::string getUri() const;
    std::string getMethod() const;
    std::string getHttpVersion() const;
    std::string getBody() const;
    std::map<std::string, std::string> getHeaders() const;
    std::string getAllHeaders() const;
};

std::ostream &operator<<(std::ostream &o, RequestData const &i);
