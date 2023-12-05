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
            std::cout << GREEN_TEXT << this->resourcesWithRoot << " Not ended with /" << RESET_COLOR << std::endl;
            return new Conflict409(this->config.errorPages["409"]);
        }
        else {
            std::cout << RED_TEXT << this->resourcesWithRoot << " ended with /" << RESET_COLOR << std::endl;
            if (checkLocationIncludesCgi()) {
                std::cout << GREEN_TEXT << "location icnludes cgi" << RESET_COLOR << std::endl;
                if (!checkIndexFilesInDir()) {
                    std::cout << RED_TEXT << "no index file on dir" << RESET_COLOR << std::endl;
                    return new Forbidden403(this->config.errorPages["403"]);
                }
                else {
                    std::cout << GREEN_TEXT << "there is index file on dir" << RESET_COLOR << std::endl;
                    //run cgi on requested file with DELETE request_method
                }
            }
            //location doesn't include cgi
            else {
                std::cout << RED_TEXT << "location doesn't include cgi" << RESET_COLOR << std::endl;
                if (deleteDirContent()) {
                    std::cout << GREEN_TEXT << "content on dir deleted" << RESET_COLOR << std::endl;
                    return new NoContent204(this->config.errorPages["204"]);
                }
                //in case of unable to clear the folder content
                else {
                    std::cout << RED_TEXT << "unable to clear dir" << RESET_COLOR << std::endl;
                    if (!checkWriteAccessOnDir()) {
                        std::cout << RED_TEXT << "write access is not allowed" << RESET_COLOR << std::endl;
                        return new Forbidden403(this->config.errorPages["403"]);
                    }
                    else {
                        std::cout << GREEN_TEXT << "write access is allowed" << RESET_COLOR << std::endl;
                        return new InternalServerError500(this->config.errorPages["500"]);
                    }
                }

            }
        }

    }
    //we request a file here
    else {
        std::cout << BLUE_TEXT << this->resourcesWithRoot << " is a dir" << RESET_COLOR << std::endl;
        if (checkLocationIncludesCgi()) {
            //run cgi on requested file with DELETE request method
        }
        //requested location doesn't have cgi
        else {
            deleteFile();
            return new NoContent204(this->config.errorPages["204"]);
        }
    }

    return new NotFound404(this->target, this->config.errorPages["404"]);
}