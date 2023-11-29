#include "Forbidden403.hpp"

Forbidden403::Forbidden403(std::string const &errorPage) {
    this->statusCode = "403";
    this->statusMessage = "Forbidden";
    this->headers["Content-Type"] = "text/html";
    this->headers["Date"] = getCurrentTime();
    this->errorPath = errorPage;
    //error page
    if (!access(errorPath.c_str(), F_OK | R_OK))
        this->errorPath = errorPath;
    else
        this->errorPath = STATIC_403;
}

std::string Forbidden403::createResponse() {
    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";
    response << startLine;

    std::map<std::string, std::string>::iterator it;
    for (it = headers.begin(); it != headers.end(); ++it)
        response << it->first << ": " << it->second << "\r\n";
    response << "\r\n";

    // create body
    std::ifstream file1(this->errorPath, std::ios::binary);
    std::ostringstream fileContent;
    fileContent << file1.rdbuf();
    response << fileContent.str();

    return response.str();
}