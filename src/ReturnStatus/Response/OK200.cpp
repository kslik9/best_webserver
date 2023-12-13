#include "OK200.hpp"



OK200::OK200(std::string &resource) {
    this->statusCode = "200";
    this->statusMessage = "OK";
    this->resourcePath = resource;
    this->headers["Content-Type"] = get_mime_type(resource);
    this->headers["Date"] = getCurrentTime();
    this->autoIndex = false;
}

OK200::OK200(std::string &resource, std::string const &url, bool autoIndex) {
    this->statusCode = "200";
    this->statusMessage = "OK";
    this->resourcePath = resource;
    this->headers["Content-Type"] = "text/html";
    this->headers["Date"] = getCurrentTime();
    this->autoIndex = true;
    this->target = url;
}

OK200::~OK200() {
    this->headers.clear();
}

std::string OK200::getListing() {
    std::string dir = this->resourcePath;
    DIR *directory;
    struct dirent   *entry;


    if ((directory = opendir(dir.c_str())) != NULL) {
        response << "<html>\n";
        response << "<head><title>Index of " << this->target << "</title></head>\n";
        response << "<body>\n";
        response << "<pre>\n";
        response << "<h1>Index of " << this->target << "</h1>\n";
        while ((entry = readdir(directory)) != NULL) {
            // std::cout << entry->d_name << std::endl;
            response << "<a href=\"" << entry->d_name << "\">" << entry->d_name << "</a>\n";
        }
        response << "</pre>\n";
        response << "</body>\n";
        response << "</html>\n";
        closedir(directory);
    }
    else {
        std::cerr << "error\n";
    }
    return response.str();
}

std::string OK200::createResponse() {
    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";

    std::map<std::string, std::string>::iterator it;
    response << startLine;
    for (it = headers.begin(); it != headers.end(); ++it)
        response << it->first << ": " << it->second << "\r\n";
    response << "\r\n";

    //create listing if autoIndexIsOn
    if (autoIndex == true) {
        return getListing();
    }
    //create body if autoIndexIsOff
    std::ifstream file1(this->resourcePath, std::ios::binary);
    std::ostringstream fileContent;
    fileContent << file1.rdbuf();
    response << fileContent.str();
    return response.str();
}