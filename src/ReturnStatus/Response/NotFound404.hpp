#pragma once
#include "AResponseMessage.hpp"

class AResponseMessage;

class NotFound404 : public AResponseMessage  {
    public:
        NotFound404(std::string &targetp, std::string &errorPath);
        ~NotFound404();
        std::string createResponse();
};