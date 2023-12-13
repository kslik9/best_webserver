#pragma once
#include "AResponseMessage.hpp"

class BadRequest400 : public AResponseMessage {
    public:
        BadRequest400(std::string &errorPath);
        ~BadRequest400();
        std::string createResponse();
};