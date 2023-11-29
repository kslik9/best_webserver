#include "AResponseMessage.hpp"

class OK200 : public AResponseMessage {
    private:
        std::string resourcePath;
        bool        autoIndex;
        std::string getListing();
    public:
        OK200(std::string &resource);
        OK200(std::string &resource, bool autoIndex);
        std::string createResponse();
};