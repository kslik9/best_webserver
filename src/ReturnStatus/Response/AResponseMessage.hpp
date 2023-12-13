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
#include <dirent.h>


// Consts
// #define BUFFER_SIZE (1024 * 1024) // 1MB
#define STATIC_201 "static/default_errors/201.html"
#define STATIC_204 "static/default_errors/204.html"
#define STATIC_400 "static/default_errors/500.html"
#define STATIC_403 "static/default_errors/403.html"
#define STATIC_404 "static/default_errors/404.html"
#define STATIC_405 "static/default_errors/405.html"
#define STATIC_409 "static/default_errors/409.html"
#define STATIC_413 "static/default_errors/413.html"
#define STATIC_414 "static/default_errors/414.html"
#define STATIC_500 "static/default_errors/500.html"


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
std::string get_mime_type(const std::string &fileName);