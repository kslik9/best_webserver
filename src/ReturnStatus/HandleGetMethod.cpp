#include "HttpRequestChecker.hpp"

AResponseMessage    *HttpRequestChecker::handleGetMethod() {
    std::map<std::string, std::string> abstractErrorPages;
    abstractErrorPages["404"] = "errors/404.html";
    abstractErrorPages["403"] = "errors/403.html";


    if(!checkContentExistsInRoot()) {
        std::cout << RED_TEXT <<  "`" << this->resourcesWithRoot << "` doesn't exist in root " << RESET_COLOR << std::endl;
        return new NotFound404(this->target, abstractErrorPages["404"]);
    }
    
    std::cout << GREEN_TEXT << "`" << this->resourcesWithRoot << "` exists in root" << RESET_COLOR << std::endl;
    //we check if the uri is dir or file
    if (checkContentIsDir()) {
        std::cout << BLUE_TEXT << this->resourcesWithRoot << " is a dir" << RESET_COLOR << std::endl;
        if (!checkDirIndedWithBackSlash()) {
            std::string targetWithBackSlash = this->target + "/";
            std::cout << RED_TEXT << "`" << targetWithBackSlash << "` not ended with /" << RESET_COLOR << std::endl;
            return new MovedPermanently301(targetWithBackSlash);
        }
        std::cout << GREEN_TEXT << "`" << this->target << "` ended with /" << RESET_COLOR << std::endl;;
        if (checkIndexFilesInDir()) {
            std::cout << GREEN_TEXT << "index files found: " << this->resourcesWithRoot << RESET_COLOR << std::endl;
            if (checkLocationIncludesCgi()) {
                //run cgi on requested file with GET request method
            }
            else {
                return new OK200(this->resourcesWithRoot);
            }
        }

        else {
            std::cout << RED_TEXT << "index files not found: " << this->resourcesWithRoot << RESET_COLOR << std::endl;
            if (checkAutoIndexOn()) {
                std::cout << GREEN_TEXT << "autoindex: on" << RESET_COLOR << std::endl;
                return new OK200(this->resourcesWithRoot, this->target, true);
            }
            else {
                std::cout << RED_TEXT << "autoindex: off" << RESET_COLOR << std::endl;
                return new Forbidden403(abstractErrorPages["403"]);
            }
        }
    }
    else {
        std::cout << BLUE_TEXT << "`" << this->resourcesWithRoot << "` is a file" << RESET_COLOR << std::endl;
        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with GET request method
        }
        else {
            return new OK200(this->resourcesWithRoot);
        }
    }
    return new NotFound404(this->target, abstractErrorPages["404"]);
}


