#include "HttpRequestFlow.hpp"

AResponseMessage    *HttpRequestFlow::handleDeleteMethod() {

    if(!checkContentExistsInRoot())
        return new NotFound404(this->target, this->config.errorPages["404"]);

    //we check if the uri is dir
    if (checkContentIsDir()) {
        if (!checkDirIndedWithBackSlash()) 
            return new Conflict409(this->config.errorPages["409"]);
        else {
            if (checkLocationIncludesCgi()) {
                if (!checkIndexFilesInDir())
                    return new Forbidden403(this->config.errorPages["403"]);
                else 
                    return new ResponseFromCgi(this->requestData, this->location["root"]);
            }
            //location doesn't include cgi
            else {
                if (deleteDirContent())
                    return new NoContent204(this->config.errorPages["204"]);
                //in case of unable to clear the folder content
                else {
                    if (!checkWriteAccessOnDir())
                        return new Forbidden403(this->config.errorPages["403"]);
                    else 
                        return new InternalServerError500(this->config.errorPages["500"]);
                }

            }
        }

    }
    //we request a file here
    else {
        if (checkLocationIncludesCgi())
            return new ResponseFromCgi(this->requestData, this->location["root"]);
        else {
            deleteFile();
            return new NoContent204(this->config.errorPages["204"]);
        }
    }

    return new InternalServerError500(this->config.errorPages["500"]);
}