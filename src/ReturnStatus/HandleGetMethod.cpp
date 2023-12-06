#include "HttpRequestChecker.hpp"

AResponseMessage    *HttpRequestChecker::handleGetMethod() {
    if(!checkContentExistsInRoot()) {
        std::cout << RED_TEXT <<  "`" << this->resourcesWithRoot << "` doesn't exist in root " << RESET_COLOR << std::endl;
        return new NotFound404(this->target, this->config.errorPages["404"]);
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
                std::cout << GREEN_TEXT << "cgi exists in location" << RESET_COLOR << std::endl;
                return new ResponseFromCgi(this->requestData, this->location["root"]);
            }
            else {
                std::cout << GREEN_TEXT << "file served" << RESET_COLOR << std::endl;
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
                return new Forbidden403(this->config.errorPages["403"]);
            }
        }
    }
    else {
        std::cout << BLUE_TEXT << "`" << this->resourcesWithRoot << "` is a file" << RESET_COLOR << std::endl;
        if (checkLocationIncludesCgi()) {
            std::cout << GREEN_TEXT << "cgi exists in location" << RESET_COLOR << std::endl;
            return new ResponseFromCgi(this->requestData, this->location["root"]);
        }
        else {
            std::cout << RED_TEXT << "cgi doesn't exist in location or resource not ended with .php" << RESET_COLOR << std::endl;
            std::cout << GREEN_TEXT << "file served" << RESET_COLOR << std::endl;
            return new OK200(this->resourcesWithRoot);
        }
    }
    return new NotFound404(this->target, this->config.errorPages["400"]);
}


