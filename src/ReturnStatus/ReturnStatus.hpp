#pragma once

#include "webserv.hpp"

class ReturnStatus {
    private:
        std::string message403;
        std::string message404;
    public:
        ReturnStatus();
        std::string forbidden_403();
        std::string notFound_404();
};
