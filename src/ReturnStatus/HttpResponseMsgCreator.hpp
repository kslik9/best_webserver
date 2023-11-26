#pragma once
#include "webserv.hpp"

class RequestData;

class HttpResponseMsgCreator {
    private:
        std::string statusCode;
        std::string statusMessage;
        std::string body;
        // RequestData request;
    public:
        HttpResponseMsgCreator(RequestData &request);
};