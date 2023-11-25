#pragma once
#include "webserv.hpp"

class Config;

class HttpMessage {
    private:
        std::string statusCode;
        std::string statusMessage;
        std::string target;
        std::string method;
        bool        checkNotAllowededChars();
        bool        checkUriLength();
        bool        checkRequestBodyTooLarge();
        bool        checkNoLocationMatchRequestUri();
        bool        checkLocationHasRedirection();
        bool        checkMethodNotAllowed();
        bool        checkContentNotExistInRoot();
        bool        checkContentIsDir();
        bool        checkIndexFilesInDir();
        bool        checkAutoIndexOn();
        bool        checkLocationIncludesCgi();

        Config &config;
    public:
        HttpMessage(std::string const &request, Config &config);
        std::string getStatusCode();
        void        createHttpHeader();
        void        checkRequest();
        void        handleGetMethod();
};