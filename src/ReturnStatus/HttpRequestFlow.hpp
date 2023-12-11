#pragma once
#include "webserv.hpp"

class   RequestData;
class   AResponseMessage;
class   ServConf;

class HttpRequestFlow {
    private:
        std::string                         statusCode;
        std::string                         statusMessage;
        std::string                         target;
        std::string                         method;
        std::string                         resources;
        std::string                         resourcesWithRoot;
        int                                 contentLen;
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
        bool                                checkLocationSupportUpload(std::string &uploadDir);
        bool                                fileExceedsMaxSize();
        bool                                uploadFile(std::string partTwo);
        ServConf                            &config;
        std::map<std::string, std::string>  location;
        bool                                deleteFile();
        AResponseMessage    *handleGetMethod();
        AResponseMessage    *handlePostMethod();
        AResponseMessage    *handleDeleteMethod();
        RequestData &requestData;
    public:
        AResponseMessage    *checkRequestAndReturnHttpMessage();
        HttpRequestFlow(RequestData &requestData, ServConf &servConf);
        void        createHttpHeader();
        void        setContentLen(int contentLen);
           
};

