#include "Created201.hpp"

Created201::Created201() {
    statusCode = "201";
    statusMessage = "Created";
    //headers
    headers["Date"] = getCurrentTime();
    headers["Content-Type"] = "text/html";

    this->errorPath = STATIC_201;
}

std::string Created201::createResponse() {
    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";
    std::map<std::string, std::string>::iterator it;
    response << startLine;
    for (it = headers.begin(); it != headers.end(); ++it)
        response << it->first << ": " << it->second << "\r\n"; //similar to: "Content-Type: " << mime_type << "\r\n"
    response << "\r\n";

    //create body
    std::ifstream file1(this->errorPath, std::ios::binary);
    std::ostringstream fileContent;
    fileContent << file1.rdbuf();
    response << fileContent.str();
    return response.str();
}