#pragma once
#include "webserv.hpp"

class RequestData {
    private:
        std::string uri;
        std::string method;
    public:
        RequestData(std::string &request);
        std::string getUri() const;
        std::string getMethod() const;
};