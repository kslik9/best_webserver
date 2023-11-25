#include "ReturnStatus.hpp"

ReturnStatus::ReturnStatus() {
    //create 403 error page
    std::stringstream header;
    std::ostringstream fileContent;

    header << "HTTP/1.1 403 Forbidden\r\n"
            << "Content-Type: text/html\r\n\r\n";
    this->message403 = header.str();
    std::ifstream file1(STATIC_403, std::ios::binary);
    fileContent << file1.rdbuf();
    this->message403 += fileContent.str();
    header.str("");
    fileContent.str("");

    //create 404 error page
    header << "HTTP/1.1 404 Not Found\r\n"
            << "Content-Type: text/html\r\n\r\n";
    this->message404 = header.str();
    std::ifstream file2(STATIC_404, std::ios::binary);
    fileContent << file2.rdbuf();
    this->message404 += fileContent.str();
}

std::string ReturnStatus::forbidden_403() {
    return this->message403;
}

std::string ReturnStatus::notFound_404() {
    return this->message404;
}