#include "AResponseMessage.hpp"

class Conflict409 : public AResponseMessage {
    public:
        Conflict409(std::string &errorPath);
        std::string createResponse();
};