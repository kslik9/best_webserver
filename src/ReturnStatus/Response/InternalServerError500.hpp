#include "AResponseMessage.hpp"

class InternalServerError500 : public AResponseMessage {
    public:
        InternalServerError500(std::string &errorPath);
        ~InternalServerError500();
        std::string createResponse();
};