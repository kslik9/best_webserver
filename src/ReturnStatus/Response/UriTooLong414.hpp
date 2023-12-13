#pragma once
#include "AResponseMessage.hpp"

class AResponseMessage;

class UriTooLong414 : public AResponseMessage  {
    public:
        UriTooLong414(std::string &errorPath);
        ~UriTooLong414();
        std::string createResponse();
};