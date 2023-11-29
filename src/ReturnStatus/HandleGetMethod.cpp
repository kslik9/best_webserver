#include "HttpRequestChecker.hpp"

AResponseMessage    *HttpRequestChecker::handleGetMethod() {
    std::map<std::string, std::string> abstractErrorPages;
    abstractErrorPages["404"] = "errors/404.html";

    if(!checkContentExistsInRoot()) {
        std::cout << "`" << location["root"] + this->resources << "` not exist in root\n";
        return new NotFound404(this->target, abstractErrorPages["404"]);
    }
    
    //we check if the uri is dir or file
    if (checkContentIsDir()) {
        std::cout << this->resourcesWithPath << " is a dir\n";
        if (!checkDirIndedWithBackSlash()) {
            std::string targetWithBackSlash = this->target + "/";
            std::cout << "`" << targetWithBackSlash << "` not ended with /\n";
            return new MovedPermanently301(targetWithBackSlash);
        }
        std::cout << "`" << this->target << "` ended with /\n";
        if (checkIndexFilesInDir()) {
            std::cout << "index files: found\n";
            if (checkLocationIncludesCgi()) {
                //run cgi on requested file with GET request method
            }
            else {
                return new OK200(this->resourcesWithPath);
            }
        }
        else {
            if (checkAutoIndexOn()) {
                std::cout << "autoindex: on\n";
                return new OK200(this->resourcesWithPath, true);
            }
            else {
                std::cout << "autoindex: off\n";
                return new Forbidden403();
            }
        }
    }
    else {
        std::cout << "i am file " << this->resourcesWithPath << std::endl;

        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with GET request method
        }
        else {
            return new OK200(this->resourcesWithPath);
        }
    }
    return new NotFound404(this->target, abstractErrorPages["404"]);
}


