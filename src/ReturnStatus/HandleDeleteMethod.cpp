#include "HttpRequestChecker.hpp"

void HttpRequestChecker::handleDeleteMethod() {

    if(!checkContentExistsInRoot()) {
        //create 404 Not Found
        //this->statusCode = 404
        //this->statusMessage = Not Found
        //return
    }

    //we check if the uri is dir (has '/' at end)
    if (checkContentIsDir()) {

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
}