#pragma once
#include "webserv.hpp"

class   RequestData;
class   AResponseMessage;
class   ServConf;

class HttpRequestFlow {
    private:
        std::string                         statusMessage;
        std::string                         target;
        std::string                         method;
        std::string                         resources;
        std::string                         resourcesWithRoot;
        bool                                checkNotAllowededChars();
        bool                                checkUriLength();
        bool                                checkRequestHttpMessage();
        bool                                checkLocationMatchRequestUri();
        bool                                checkLocationHasRedirection();
        bool                                checkMethodAllowed(std::string &allowedMethod);
        bool                                checkContentExistsInRoot();
        bool                                checkContentIsDir();
        bool                                checkIndexFilesInDir();
        bool                                checkAutoIndexOn();
        bool                                checkLocationIncludesCgi();
        bool                                checkDirIndedWithBackSlash();
        bool                                deleteDirContent();
        bool                                checkWriteAccessOnDir();
        bool                                checkLocationSupportUpload();
        bool                                handlePost();
        bool                                checkFilEexceedMaxSize();
        RequestData                         &requestData;
        ServConf                            &config;
        std::map<std::string, std::string>  location;
        bool                                deleteFile();
        int                                 bodySize;
        AResponseMessage                    *handleGetMethod();
        AResponseMessage                    *handlePostMethod();
        AResponseMessage                    *handleDeleteMethod();
    public:
        HttpRequestFlow(RequestData &requestData, ServConf &servConf);
        ~HttpRequestFlow();
        void    setBodySize(int bodySizeP);
        int     getBodySize();
        AResponseMessage    *checkRequestAndReturnHttpMessage();
};

