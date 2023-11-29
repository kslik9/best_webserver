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
            std::cout << "kayn azzin\n";
            if (checkLocationIncludesCgi()) {
                //run cgi on requested file with GET request method
            }
            else {
                return new OK200(this->resourcesWithPath, false);
            }
        }
        else {
            if (checkAutoIndexOn()) {
                std::cout << "autoindex abb\n";
                return new OK200(this->resourcesWithPath, true);
            }
            else {
                // return new OK200(this->resourcesWithPath, false);
            }
        }
    }
    else {
        std::cout << "i am file " << this->resourcesWithPath << std::endl;

        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with GET request method
        }
        else {
            return new OK200(this->resourcesWithPath, false);
        }
    }
    return new NotFound404(this->target, abstractErrorPages["404"]);
}


