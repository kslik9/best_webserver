#pragma once
#include "AResponseMessage.hpp"

class MovedPermanently : public AResponseMessage {
    public:
        MovedPermanently(std::string &location);
        std::string createResponse();
};