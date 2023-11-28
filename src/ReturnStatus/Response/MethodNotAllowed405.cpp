#include "MethodNotAllowed405.hpp"

MethodNotAllowed405::MethodNotAllowed405(std::string &allowedMethods) {
    this->statusCode = "405";
    this->statusMessage = "Method Not Allowed";
    this->headers["Allow"] = allowedMethods;
    this->headers["Content-Type"] = "text/html";
    this->headers["Date"] = getCurrentTime();
}

std::string MethodNotAllowed405::createResponse() {
    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";
    std::map<std::string, std::string>::iterator it;
    response << startLine;
    for (it = headers.begin(); it != headers.end(); ++it)
        response << it->first << ": " << it->second << "\r\n";
    response << "\r\n";

    response << "<h1>Method Not Allowed</h1>";
    return response.str();
}