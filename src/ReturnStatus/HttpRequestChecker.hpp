#pragma once
#include "webserv.hpp"

// #include "RequestData.hpp"
// class Config;
class RequestData;
class AResponseMessage;
class   ServConf;

class HttpRequestChecker {
    private:
        std::string statusCode;
        std::string statusMessage;
        std::string target;
        std::string method;
        std::string resources;
        std::string resourcesWithRoot;
        bool        checkNotAllowededChars();
        bool        checkUriLength();
        bool        checkRequestHttpMessage();
        bool        checkLocationMatchRequestUri();
        bool        checkLocationHasRedirection();
        bool        checkMethodAllowed(std::string &allowedMethod);
        bool        checkContentExistsInRoot();
        bool        checkContentIsDir();
        bool        checkIndexFilesInDir();
        bool        checkAutoIndexOn();
        bool        checkLocationIncludesCgi();
        bool        checkDirIndedWithBackSlash();
        bool        CheckDeleteDirContent();
        bool        checkWriteAccessOnDir();
        bool        checkLocationSupportUpload();
        // Config      &config;
        ServConf    &config;
        std::map<std::string, std::string> location;
    public:
        RequestData &requestData;
        HttpRequestChecker(RequestData &requestData, ServConf &servConf);
        std::string getStatusCode();
        void        createHttpHeader();
        
        AResponseMessage    *checkRequestAndReturnHttpMessage();
        AResponseMessage    *handleGetMethod();
        AResponseMessage    *handlePostMethod();
        AResponseMessage    *handleDeleteMethod();
};

