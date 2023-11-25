#include "HttpMessage.hpp"

void parse_request(const std::string &request, std::string &method, std::string &target) {
	try
	{
		std::istringstream iss(request);
		iss >> method >> target;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		method = "GET";
		target = "/";
	}
}

HttpMessage::HttpMessage(std::string const &request, Config &config) : config(config) {
    parse_request(request, this->method, this->target);
}

std::string HttpMessage::getStatusCode() {
    return this->statusCode;
}

void    HttpMessage::createHttpHeader() {
    
}





void    HttpMessage::checkRequest() {
    if (checkNotAllowededChars()) {
        //create 400 bad request ()
        //this->statusCode = 400
        //this->statusMessage = "Bad Request"
        //return errorpage
    }
    if (checkUriLength()) {
        //create 414 Request-URI Too Long
        //this->statusCode = 414
        //this->statusMessage = Request-URI Too Long
        // return errorPage
    }
    if (checkRequestBodyTooLarge()) {
        //create 413 Request Entity Too Large
        //this->statusCode = 413
        //this->statusMessage = Request Entity Too Large
        // return errorPage
    }
    if (checkNoLocationMatchRequestUri()) {
        //create 404 Not Found
        //this->statusCode = 404
        //this->statusMessage = Not Found
        // return errorPage
    }
    if (checkLocationHasRedirection()) {
        //create 301 Moved Permanently
        //this->statusCode = 301
        //this->statusMessage = MOved Permanently
        //return Page
    }
    if (checkMethodNotAllowed()) {
        //create 405 Method Not Allowed
        //this->statusCode = 405
        //this->statusMessage = Method Not Allowed
        //return Page
    }

    //now we check the request method
    //////////////////////////////// GET ///////////////////////////
    if (method == "GET") {
        if(checkContentNotExistInRoot()) {
        //create 404 Not Found
        //this->statusCode = 404
        //this->statusMessage = Not Found
        //return Page
        }
        if (checkContentIsDir() && !checkIndexFilesInDir()) {
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
        //the content type is dir but it include index files in dir [or] the content type is file or 
        else if ((checkContentIsDir() && checkIndexFilesInDir()) || !checkContentIsDir()) {
            if (checkLocationIncludesCgi()) {
                //run cgi on request file
                //return depends on cgi
            }
            //location will run static pages
            else {
                //return requested file
                //status code 200
                //statusmessge OK
            }
        }
    }
}