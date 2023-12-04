#include "HttpRequestChecker.hpp"

HttpRequestChecker::HttpRequestChecker(RequestData &requestData, ServConf &servConf) : requestData(requestData), config(servConf) {
    this->target = requestData.getUri();
    this->method = requestData.getMethod();
}

std::string HttpRequestChecker::getStatusCode() {
    return this->statusCode;
}

void    HttpRequestChecker::createHttpHeader() {
    
}


//this will check the request and at the end it will create an http message and return it
AResponseMessage *HttpRequestChecker::checkRequestAndReturnHttpMessage() {
    std::map<std::string, std::string> abstractErrorPages;
    abstractErrorPages["404"] = "errors/404.html";

    //////////////////////// check if req formed well /////////////////////////////
    if (checkNotAllowededChars()) {
        this->statusCode = "400";
        this->statusMessage = "Bad Request";
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
        std::cout << RED_TEXT << "Not matched" << RESET_COLOR << std::endl;
        return new NotFound404(this->target, this->config.errorPages["404"]);
    }
    if (checkLocationHasRedirection()) {
        std::cout << BLUE_TEXT << "redirected" << RESET_COLOR << std::endl;
        return new MovedPermanently301(this->location["redirect"]);
    }

    //check if the method allowed in location
    std::string allowedMethods;
    if (!checkMethodAllowed(allowedMethods)) {
        std::cout << RED_TEXT << "method not allowed hh" << location["root"] << RESET_COLOR << std::endl;
        return new MethodNotAllowed405(allowedMethods, this->config.errorPages["405"]);
    }


    //now we check the request method
    //////////////////////////////// GET ///////////////////////////
    if (method == "GET" || method == "HEAD")
        return handleGetMethod();
    else if (method == "POST")
        return handlePostMethod();
    else if (method == "DELETE")
        return handleDeleteMethod();

    return new MethodNotAllowed405(this->target, abstractErrorPages["405"]);
}