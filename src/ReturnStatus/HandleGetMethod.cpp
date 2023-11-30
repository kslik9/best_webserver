#include "HttpRequestChecker.hpp"

AResponseMessage    *HttpRequestChecker::handleGetMethod() {
    std::map<std::string, std::string> abstractErrorPages;
    abstractErrorPages["404"] = "errors/404.html";
    abstractErrorPages["403"] = "errors/403.html";


    if(!checkContentExistsInRoot()) {
        std::cout << "`" << this->resourcesWithRoot << "` doesn't exist in root\n";
        return new NotFound404(this->target, abstractErrorPages["404"]);
    }
    
    std::cout << "`" << this->resourcesWithRoot << "` exists in root\n";
    //we check if the uri is dir or file
    if (checkContentIsDir()) {
        std::cout << this->resourcesWithRoot << " is a dir\n";
        if (!checkDirIndedWithBackSlash()) {
            std::string targetWithBackSlash = this->target + "/";
            std::cout << "`" << targetWithBackSlash << "` not ended with /\n";
            return new MovedPermanently301(targetWithBackSlash);
        }
        std::cout << "`" << this->target << "` ended with /\n";
        if (checkIndexFilesInDir()) {
            std::cout << "index files found: " << this->resourcesWithRoot << std::endl;
            if (checkLocationIncludesCgi()) {
                //run cgi on requested file with GET request method
            }
            else {
                return new OK200(this->resourcesWithRoot);
            }
        }

        else {
            std::cout << "index files not found: " << this->resourcesWithRoot << std::endl;
            if (checkAutoIndexOn()) {
                std::cout << "autoindex: on\n";
                return new OK200(this->resourcesWithRoot, this->target, true);
            }
            else {
                std::cout << "autoindex: off\n";
                return new Forbidden403(abstractErrorPages["403"]);
            }
        }
    }
    else {
        std::cout << "`" << this->resourcesWithRoot << "` is a file\n";
        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with GET request method
        }
        else {
            return new OK200(this->resourcesWithRoot);
        }
    }
    return new NotFound404(this->target, abstractErrorPages["404"]);
}


