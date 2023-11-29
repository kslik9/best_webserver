#include "AResponseMessage.hpp"

class OK200 : public AResponseMessage {
    private:
        std::string resourcePath;
    public:
        OK200(std::string &resource);
        std::string createResponse();
};