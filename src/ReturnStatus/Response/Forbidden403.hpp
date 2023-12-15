#include "AResponseMessage.hpp"

class Forbidden403 : public AResponseMessage {
    private:
        std::string resourcePath;
    public:
        Forbidden403(std::string const &errorPage);
        std::string createResponse();
};