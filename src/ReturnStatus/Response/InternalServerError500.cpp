#include "InternalServerError500.hpp"

InternalServerError500::InternalServerError500(std::string &errorPath) {
    this->statusCode = "500";
    this->statusMessage = "Internal Server Error";
    this->headers["Content-Type"] = "text/plain";
    this->headers["Date"] = getCurrentTime();

    if (!access(errorPath.c_str(), F_OK | R_OK))
        this->errorPath = errorPath;
    else
        this->errorPath = STATIC_500;
}

InternalServerError500::~InternalServerError500() {
    this->headers.clear();
}

std::string InternalServerError500::createResponse() {
    std::map<std::string, std::string>::iterator it;

    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";
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