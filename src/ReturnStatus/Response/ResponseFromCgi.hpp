#pragma once
#include "AResponseMessage.hpp"
#include "../RequestData.hpp"

typedef struct
{
    std::string path;
    std::ifstream *file_stream;
}   php_script;

class ResponseFromCgi : public AResponseMessage {
    private:
        RequestData &rq;
        std::map<std::string, std::string> keyValue;
	    std::vector<const char *> env_vec;
        void init_env(RequestData request);
        std::string process();
    public:
        ResponseFromCgi(RequestData &rq);
        std::string createResponse();
};