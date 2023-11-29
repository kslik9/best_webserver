#include "HttpRequestChecker.hpp"

AResponseMessage    *HttpRequestChecker::handleGetMethod() {
    std::map<std::string, std::string> abstractErrorPages;
    abstractErrorPages["404"] = "errors/404.html";

    if(!checkContentExistsInRoot()) {
        std::cout << "not found in root\n";
        return new NotFound404(this->target, abstractErrorPages["404"]);
    }
    
    //we check if the uri is dir or file
    if (checkContentIsDir()) {
        std::cout << this->resourcesWithPath << " is a dir\n";
        if (!checkDirIndedWithBackSlash()) {
            std::string targetWithBackSlash = this->target + "/";
            std::cout << "not ended with Slash and will be forwaded to link with " << targetWithBackSlash << std::endl;
            return new MovedPermanently301(targetWithBackSlash);
        }
        if (checkIndexFilesInDir()) {
            if (checkLocationIncludesCgi()) {
                //run cgi on requested file with GET request method
            }
            else {
                //create 200 OK
                //return requested file
            }
        }
        else {
            if (checkAutoIndexOn()) {
                //return autoindex of the directory
                //statusCode  = 200
                //statusMessge = OK
            }
            else {
                //create 403 Forbidden
                //this->statusCode = 403
                //this->statusMessage = Forbidden
                //return errorPage
            }
        }
    }
    else {
        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with GET request method
        }
        else {
            //create 200 OK
            //return requested file
        }
    }
    return new NotFound404(this->target, abstractErrorPages["404"]);
}