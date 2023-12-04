#include "HttpRequestChecker.hpp"

AResponseMessage    *HttpRequestChecker::handlePostMethod() {
    std::map<std::string, std::string> abstractErrorPages;
    abstractErrorPages["404"] = "errors/404.html";
    abstractErrorPages["403"] = "errors/403.html";
    // std::map<std::string, std::string> abstractErrorPages;
    // abstractErrorPages["404"] = "errors/404.html";
    // abstractErrorPages["403"] = "errors/403.html";
    //check if location support upload
    if(checkLocationSupportUpload()) {
        //upload the post request body
        //create `201 Created` http response message
        //return ;
    }

    if(!checkContentExistsInRoot()) {
        std::cout << RED_TEXT <<  "`" << this->resourcesWithRoot << "` doesn't exist in root " << RESET_COLOR << std::endl;
        return new NotFound404(this->target, abstractErrorPages["404"]);
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
                //run cgi on requested file with GET request method
            }
            else {
                //create 403 Forbidden
                //return requested file
                
            }
        }
        else {
            std::cout << RED_TEXT << "index files not found: " << this->resourcesWithRoot << RESET_COLOR << std::endl;
            std::cout << GREEN_TEXT << "index files found: " << this->resourcesWithRoot << RESET_COLOR << std::endl;

        }
    }
    //we request a file here
    else {
        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with POST request method
        }
        else {
            //create 403 Forbidden
            //this->statusCode = 403
            //this->statusMessage = Forbidden
            //return errorPage
        }
    }

    std::cout << "end\n";
    return new NotFound404(this->target, abstractErrorPages["404"]);
}