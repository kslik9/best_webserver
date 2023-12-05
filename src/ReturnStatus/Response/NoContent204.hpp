#include "AResponseMessage.hpp"

class NoContent204 : public AResponseMessage {
    public:
        NoContent204(std::string &errorPath);
        std::string createResponse();
};