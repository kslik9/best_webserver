#pragma once
#include "webserv.hpp"

class Config;
class RequestData;

class HttpMessageChecker {
    private:
        std::string statusCode;
        std::string statusMessage;
        std::string target;
        std::string method;
        bool        checkNotAllowededChars();
        bool        checkUriLength();
        bool        checkRequestHttpMessage();
        bool        checkLocationMatchRequestUri();
        bool        checkLocationHasRedirection();
        bool        checkMethodAllowed();
        bool        checkContentExistsInRoot();
        bool        checkContentIsDir();
        bool        checkIndexFilesInDir();
        bool        checkAutoIndexOn();
        bool        checkLocationIncludesCgi();
        bool        checkDirIndedWithBackSlash();

        Config      &config;
    public:
        RequestData &requestData;
        HttpMessageChecker(RequestData &requestData, Config &config);
        std::string getStatusCode();
        void        createHttpHeader();
        void        checkRequestAndReturnHttpMessage();
        void        handleGetMethod();
        void        handlePostMethod();
        void        handleDeleteMethod();
};