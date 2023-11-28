#include "MovedPermanently.hpp"

MovedPermanently::MovedPermanently(std::string &location) {
    this->statusCode = "301";
    this->statusMessage = "Moved Permanently";
    headers["Location"] = location;
    headers["Content-Type"] = "text/html";
}

std::string MovedPermanently::createResponse() {
    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";
    std::map<std::string, std::string>::iterator it;
    response << startLine;
    for (it = headers.begin(); it != headers.end(); ++it)
        response << it->first << ": " << it->second << "\r\n";
    response << "\r\n";
    return response.str();
}