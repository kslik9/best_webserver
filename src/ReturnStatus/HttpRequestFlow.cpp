#include "HttpRequestFlow.hpp"

HttpRequestFlow::HttpRequestFlow(RequestData &requestData, ServConf &servConf) : requestData(requestData), config(servConf) {
    this->target = requestData.getUri();
    this->method = requestData.getMethod();
}

std::string HttpRequestFlow::getStatusCode() {
    return this->statusCode;
}

void    HttpRequestFlow::createHttpHeader() {
    
}


//this will check the request and at the end it will create an http message and return it
AResponseMessage *HttpRequestFlow::checkRequestAndReturnHttpMessage() {
    // return new Forbidden403(this->config.errorPages["403"]);
    std::map<std::string, std::string> abstractErrorPages;
    abstractErrorPages["404"] = "errors/404.html";

    //////////////////////// check if req formed well /////////////////////////////
    if (checkNotAllowededChars()) {
        std::cout << RED_TEXT << "not allowed chars" << RESET_COLOR << std::endl;
        return new BadRequest400(this->config.errorPages["400"]);
    }
    if (checkUriLength()) {
        std::cout << RED_TEXT << "uri too long" << RESET_COLOR << std::endl;
        return new UriTooLong414(this->config.errorPages["414"]);
    }
    if (checkRequestHttpMessage()) {
        std::cout << RED_TEXT << "body max size" << RESET_COLOR << std::endl;
        return new PayloadTooLarge(this->config.errorPages["413"]);
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
        std::cout << RED_TEXT << "method not allowed hh " << location["root"] << RESET_COLOR << std::endl;
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