#include "HttpRequestChecker.hpp"

AResponseMessage    *HttpRequestChecker::handleDeleteMethod() {

    if(!checkContentExistsInRoot()) {
        std::cout << RED_TEXT <<  "`" << this->resourcesWithRoot << "` doesn't exist in root " << RESET_COLOR << std::endl;
        return new NotFound404(this->target, this->config.errorPages["404"]);
    }

    std::cout << GREEN_TEXT << "`" << this->resourcesWithRoot << "` exists in root" << RESET_COLOR << std::endl;
    //we check if the uri is dir
    if (checkContentIsDir()) {
        std::cout << BLUE_TEXT << this->resourcesWithRoot << " is a dir" << RESET_COLOR << std::endl;
        if (!checkDirIndedWithBackSlash()) {
            //creeate 409 conflict
            //return;
        }
        else {
            //location includes cgi
            if (checkLocationIncludesCgi()) {
                if (!checkIndexFilesInDir()) {
                    //create 403 Forbidden
                }
                else {
                    //run cgi on requested file with DELETE request_method
                }
            }
            //location doesn't include cgi
            else {
                if (CheckDeleteDirContent()) {
                    //create 205 No Content
                }
                //in case of unable to clear the folder content
                else {
                    if (checkWriteAccessOnDir()) {
                        //create Internal Server Error
                    }
                    else {
                        //create 403 Forbidden
                    }
                }

            }
        }

    }
    //we request a file here
    else {
        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with DELETE request method
        }
        //requested location doesn't have cgi
        else {
            //delete the file
            //204 No Content
        }
    }

    return new NotFound404(this->target, this->config.errorPages["404"]);
}