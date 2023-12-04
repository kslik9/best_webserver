#include "Conflict409.hpp"

Conflict409::Conflict409(std::string &errorPath) {
    this->statusCode = "409";
    this->statusMessage = "Conflict";
    this->headers["Content-Type"] = "text/plain";

    if (!access(errorPath.c_str(), F_OK | R_OK))
        this->errorPath = errorPath;
    else
        this->errorPath = STATIC_409;
}

std::string Conflict409::createResponse() {
    return "response";
}