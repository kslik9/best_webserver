#pragma once
// #include "webserv.hpp"
#include <sys/wait.h>

// IO
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include <map>


// Consts
#define BUFFER_SIZE (1024 * 1024) // 1MB
#define STATIC_404 "static/default_errors/404.html"
#define STATIC_403 "static/default_errors/403.html"

class AResponseMessage {
    protected:
        std::string                         statusCode;
        std::string                         statusMessage;
        std::string                         errorPath;
        std::stringstream                   response;
        std::string                         contentType;
        std::string                         target;
        std::map<std::string, std::string>  headers;
        std::string                         startLine;
    public:
        virtual ~AResponseMessage() {};
        virtual std::string createResponse() = 0;
};

std::string getCurrentTime();