#include "NoContent204.hpp"

NoContent204::NoContent204(std::string &errorPath) {
    this->statusCode = "204";
    this->statusMessage = "No Content";
    this->headers["Date"] = getCurrentTime();
    this->headers["Content-Type"] = "text/plain";


    if (!access(errorPath.c_str(), F_OK | R_OK))
        this->errorPath = errorPath;
    else
        this->errorPath = STATIC_204;
}

std::string NoContent204::createResponse() {
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
