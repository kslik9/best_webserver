#include "HttpRequestFlow.hpp"

AResponseMessage    *HttpRequestFlow::handlePostMethod() {
    std::cout << BLUE_TEXT << "POST METHOD" << RESET_COLOR << std::endl;
    //check if location support upload
    if(checkLocationSupportUpload()) {
        std::cout << GREEN_TEXT << "file uploaded succesfully" << RESET_COLOR << std::endl;
        if (checkFilEexceedMaxSize()) {
            std::cout << RED_TEXT << "file uploaded succesfully" << RESET_COLOR << std::endl;
            return new PayloadTooLarge(this->config.errorPages["413"]);
        }
        uploadFile();
        return new Created201();
    }

    if(!checkContentExistsInRoot()) {
        std::cout << RED_TEXT <<  "`" << this->resourcesWithRoot << "` doesn't exist in root " << RESET_COLOR << std::endl;
        return new NotFound404(this->target, this->config.errorPages["404"]);
    }

    std::cout << GREEN_TEXT << "`" << this->resourcesWithRoot << "` exists in root" << RESET_COLOR << std::endl;
    //we check if the uri is dir (has '/' at end)
    if (checkContentIsDir()) {
        std::cout << BLUE_TEXT << this->resourcesWithRoot << " is a dir" << RESET_COLOR << std::endl;
        if (!checkDirIndedWithBackSlash()) {
            std::string targetWithBackSlash = this->target + "/";
            std::cout << RED_TEXT << "`" << targetWithBackSlash << "` not ended with /" << RESET_COLOR << std::endl;
            return new MovedPermanently301(targetWithBackSlash);
        }
        if (checkIndexFilesInDir()) {
            std::cout << GREEN_TEXT << "index files found: " << this->resourcesWithRoot << RESET_COLOR << std::endl;
            if (checkLocationIncludesCgi()) {
                std::cout << GREEN_TEXT << "cgi exists in location" << RESET_COLOR << std::endl;
                return new ResponseFromCgi(this->requestData, this->location["root"]);
            }
            else {
                std::cout << RED_TEXT << "cgi doensn't exist in location" << RESET_COLOR << std::endl;
                return new Forbidden403(this->config.errorPages["403"]);
            }
        }
        else {
            std::cout << RED_TEXT << "index files not found: " << this->resourcesWithRoot << RESET_COLOR << std::endl;
            return new Forbidden403(this->config.errorPages["403"]);
        }
    }
    //we request a file here
    else {
        if (checkLocationIncludesCgi()) {
            std::cout << GREEN_TEXT << "cgi exists in location" << RESET_COLOR << std::endl;
            return new ResponseFromCgi(this->requestData, this->location["root"]);
        }
        else {
            std::cout << RED_TEXT << "cgi doesn't exist in location" << RESET_COLOR << std::endl;
            return new Forbidden403(this->config.errorPages["403"]);
        }
    }
    std::cout << "end\n";
    return new NotFound404(this->target, this->config.errorPages["404"]);
}