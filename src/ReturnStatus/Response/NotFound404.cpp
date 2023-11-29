#include "NotFound404.hpp"

//contructor
NotFound404::NotFound404(std::string &targetp, std::string errorPath) {
    statusCode = "404";
    statusMessage = "Not Found";
    target = targetp;

    //headers
    headers["Date"] = getCurrentTime();
    headers["Content-Type"] = "text/html";

    //check if errorpage is exist
    if (!access(errorPath.c_str(), F_OK | R_OK))
        this->errorPath = errorPath;
    else
        this->errorPath = STATIC_404;


    
}

#include <ctime>
std::string NotFound404::createResponse() {


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

    // response << "<h1>404 Not Found</h1>";


    // return "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
    return response.str();
}