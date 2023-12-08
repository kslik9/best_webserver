#pragma once


#include <sys/wait.h>

// IO
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <memory>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
// 
#include <map>
#include <vector>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <poll.h>
#include <exception>
#include <sys/stat.h>
#include <netdb.h>


// OOP
#include "../src/Config/Config.hpp"
#include "../src/Logger/Logger.hpp"
#include "../src/Server/Server.hpp"
#include "../src/ReturnStatus/RequestData.hpp"
#include "../src/ReturnStatus/HttpRequestFlow.hpp"

#include "../src/ReturnStatus/Response/AResponseMessage.hpp"
#include "../src/ReturnStatus/Response/NotFound404.hpp"
#include "../src/ReturnStatus/Response/MovedPermanently301.hpp"
#include "../src/ReturnStatus/Response/MethodNotAllowed405.hpp"
#include "../src/ReturnStatus/Response/Forbidden403.hpp"
#include "../src/ReturnStatus/Response/Conflict409.hpp"
#include "../src/ReturnStatus/Response/NoContent204.hpp"
#include "../src/ReturnStatus/Response/InternalServerError500.hpp"
#include "../src/ReturnStatus/Response/OK200.hpp"
#include "../src/ReturnStatus/Response/ResponseFromCgi.hpp"


// 
#include "../src/CGIHandler/CGIHandler.hpp"


// Consts
#define BUFFER_SIZE 1024 * 1024 // 10MB
#define STATIC_HTTP "static/http/"

#define CLIENTS_COUNT 4000
#define RESET_COLOR "\033[0m"
#define BLUE_TEXT "\033[1;34m"
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
// 
#define CGI_BIN "cgi-bin/php-cgi"
// #define ROOT_FOLDER "/Users/aessaoud/Desktop/projects/webserv/var/www/html"
#define PATH "/Users/aessaoud/goinfre/homebrew/bin:/Users/aessaoud/goinfre/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"

class ReturnStatus;
