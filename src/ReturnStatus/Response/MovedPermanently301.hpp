#pragma once
#include "AResponseMessage.hpp"

class MovedPermanently301 : public AResponseMessage {
    public:
        MovedPermanently301(std::string &location);
        std::string createResponse();
};