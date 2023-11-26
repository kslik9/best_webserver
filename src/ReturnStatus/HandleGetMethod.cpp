#include "HttpMessageChecker.hpp"

void HttpMessageChecker::handleGetMethod() {
    std::cout << this->target << std::endl;
    if(!checkContentExistsInRoot()) {
        //create 404 Not Found
        //this->statusCode = 404
        //this->statusMessage = Not Found
        //return Page
    }

    //we check if the uri is dir (has '/' at end)
    if (checkContentIsDir()) {
        if (!checkDirIndedWithBackSlash()) {
            //creeate 301 redirection to request uri with '/' at the end
            //return;
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
}