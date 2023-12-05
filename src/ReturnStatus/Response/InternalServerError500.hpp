#include "AResponseMessage.hpp"

class InternalServerError500 : public AResponseMessage {
    public:
        InternalServerError500(std::string &errorPath);
        std::string createResponse();
};