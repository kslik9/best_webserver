#include "PayloadTooLarge413.hpp"

//contructor
PayloadTooLarge::PayloadTooLarge(std::string &errorPath) {
    statusCode = "413";
    statusMessage = "Payload Too Large";

    headers["Date"] = getCurrentTime();
    headers["Content-Type"] = "text/html";

    if (!access(errorPath.c_str(), F_OK | R_OK))
        this->errorPath = errorPath;
    else
        this->errorPath = STATIC_413;
    
}

std::string PayloadTooLarge::createResponse() {

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