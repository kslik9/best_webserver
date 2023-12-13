#pragma once
#include "AResponseMessage.hpp"

class MethodNotAllowed405 : public AResponseMessage {
    public:
        MethodNotAllowed405(std::string &allowedMethods, std::string &errorPath);
        ~MethodNotAllowed405();
        std::string createResponse();
};