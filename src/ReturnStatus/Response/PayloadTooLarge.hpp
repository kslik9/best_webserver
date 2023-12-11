#pragma once
#include "AResponseMessage.hpp"

class PayloadTooLarge : public AResponseMessage {
    public:
        PayloadTooLarge(std::string &errorPath);
        std::string createResponse();
};