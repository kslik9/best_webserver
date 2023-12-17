#include "HttpRequestFlow.hpp"

HttpRequestFlow::HttpRequestFlow(RequestData &requestData, ServConf &servConf) : requestData(requestData), config(servConf) {
    this->target = requestData.getUri();
    this->method = requestData.getMethod();
}


void    HttpRequestFlow::createHttpHeader() {
    
}


//this will check the request and at the end it will create an http message and return it
AResponseMessage *HttpRequestFlow::checkRequestAndReturnHttpMessage() {

    //////////////////////// check if req formed well /////////////////////////////
    if (checkNotAllowededChars())
        return new BadRequest400(this->config.errorPages["400"]);
    if (checkUriLength())
        return new UriTooLong414(this->config.errorPages["414"]);
    //check if no location match the request uri
    if (!checkLocationMatchRequestUri()) 
        return new NotFound404(this->target, this->config.errorPages["404"]);
    if (checkMaxBodySize())
        return new PayloadTooLarge(this->config.errorPages["413"]);
    
    if (checkLocationHasRedirection())
        return new MovedPermanently301(this->location["redirect"]);

    //check if the method allowed in location
    std::string allowedMethods;
    if (!checkMethodAllowed(allowedMethods)) 
        return new MethodNotAllowed405(allowedMethods, this->config.errorPages["405"]);


    //now we check the request method
    //////////////////////////////// GET ///////////////////////////
    if (method == "GET" || method == "HEAD")
        return handleGetMethod();
    else if (method == "POST")
        return handlePostMethod();
    else if (method == "DELETE")
        return handleDeleteMethod();

    return new MethodNotAllowed405(this->target, this->config.errorPages["405"]);
}

void    HttpRequestFlow::setBodySize(int bodySizeP) {
    this->bodySize = bodySizeP;
}

int     HttpRequestFlow::getBodySize() {
    return this->bodySize;
}