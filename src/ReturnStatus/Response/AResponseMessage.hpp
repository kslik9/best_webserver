#pragma once
#include "webserv.hpp"
#include <exception>
class AResponseMessage {
    protected:
        std::string                         statusCode;
        std::string                         statusMessage;
        std::string                         errorPath;
        std::stringstream                   response;
        std::string                         contentType;
        std::string                         target;
        std::map<std::string, std::string>  headers;
        std::string                         startLine;
    public:
        virtual ~AResponseMessage() {};
        AResponseMessage(std::string targetp) : target(targetp) {};
        virtual std::string createResponse() = 0;
};