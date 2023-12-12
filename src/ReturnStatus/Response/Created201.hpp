#pragma once
#include "AResponseMessage.hpp"

class AResponseMessage;

class Created201 : public AResponseMessage  {
    public:
        Created201();
        std::string createResponse();
};