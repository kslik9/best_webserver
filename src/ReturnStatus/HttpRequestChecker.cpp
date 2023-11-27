#include "HttpRequestChecker.hpp"

HttpRequestChecker::HttpRequestChecker(RequestData &requestData, Config &config) : requestData(requestData), config(config) {
    this->target = requestData.getUri();
    this->method = requestData.getMethod();
}

std::string HttpRequestChecker::getStatusCode() {
    return this->statusCode;
}

void    HttpRequestChecker::createHttpHeader() {
    
}




//this will check the request and at the end it will create an http message and return it
void    HttpRequestChecker::checkRequestAndReturnHttpMessage() {
    //////////////////////// check if req formed well /////////////////////////////
    if (checkNotAllowededChars()) {
        this->statusCode = "400";
        this->statusMessage = "Bad Request";
        return;
    }
    if (checkUriLength()) {
        //create 414 Request-URI Too Long
        //this->statusCode = 414
        //this->statusMessage = Request-URI Too Long
        // return errorPage
    }
    if (checkRequestHttpMessage()) {
        //create 413 Request Entity Too Large
        //this->statusCode = 413
        //this->statusMessage = Request Entity Too Large
        // return errorPage
    }
    
    //check if no location match the request uri
    if (!checkLocationMatchRequestUri()) {
        //create 404 Not Found
        //this->statusCode = 404
        //this->statusMessage = Not Found
        //return Page
        // std::cout << "not found a bb\n";
        // return ;
    }
    return;
    if (checkLocationHasRedirection()) {
        //create 301 Moved Permanently
        //this->statusCode = 301
        //this->statusMessage = MOved Permanently
        //return Page
    }

    //check if the method allowed in location
    if (checkMethodAllowed()) {
        //create 405 Method Not Allowed
        //this->statusCode = 405
        //this->statusMessage = Method Not Allowed
        //return Page
    }

    //now we check the request method
    //////////////////////////////// GET ///////////////////////////
    if (method == "GET") {
        handleGetMethod();
    }

    //return the created http response message
}