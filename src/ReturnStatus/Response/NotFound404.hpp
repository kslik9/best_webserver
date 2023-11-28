#pragma once
#include "AResponseMessage.hpp"



class NotFound404 : public AResponseMessage  {
    public:
        NotFound404(std::string &targetp, std::string errorPath);
        std::string createResponse();
};