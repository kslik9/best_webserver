#include "MovedPermanently301.hpp"

MovedPermanently301::MovedPermanently301(std::string &location) {
    this->statusCode = "301";
    this->statusMessage = "Moved Permanently";
    headers["Location"] = location;
    headers["Content-Type"] = "text/html";
    headers["Date"] = getCurrentTime();
}

std::string MovedPermanently301::createResponse() {
    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";
    std::map<std::string, std::string>::iterator it;
    response << startLine;
    for (it = headers.begin(); it != headers.end(); ++it)
        response << it->first << ": " << it->second << "\r\n";
    response << "\r\n";
    response << "<h1>301 Moved</h1>";
    return response.str();
}