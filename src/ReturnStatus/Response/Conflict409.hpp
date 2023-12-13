#include "AResponseMessage.hpp"

class Conflict409 : public AResponseMessage {
    public:
        Conflict409(std::string &errorPath);
        ~Conflict409();
        std::string createResponse();
};