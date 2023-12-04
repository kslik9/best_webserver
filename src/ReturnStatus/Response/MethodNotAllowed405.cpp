#include "MethodNotAllowed405.hpp"

MethodNotAllowed405::MethodNotAllowed405(std::string &allowedMethods, std::string &errorPath) {
    this->statusCode = "405";
    this->statusMessage = "Method Not Allowed";
    this->headers["Allow"] = allowedMethods;
    this->headers["Content-Type"] = "text/html";
    this->headers["Date"] = getCurrentTime();

    if (!access(errorPath.c_str(), F_OK | R_OK))
        this->errorPath = errorPath;
    else
        this->errorPath = STATIC_404;
}

std::string MethodNotAllowed405::createResponse() {
    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";
    std::map<std::string, std::string>::iterator it;
    response << startLine;
    for (it = headers.begin(); it != headers.end(); ++it)
        response << it->first << ": " << it->second << "\r\n";
    response << "\r\n";

    //create body
    std::ifstream file1(this->errorPath, std::ios::binary);
    std::ostringstream fileContent;
    fileContent << file1.rdbuf();
    response << fileContent.str();
    
    return response.str();
}