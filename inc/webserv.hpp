#ifndef WEBSERV_HPP
#define WEBSERV_HPP

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


// OOP
#include "../src/Config/Config.hpp"
#include "../src/Logger/Logger.hpp"
#include "../src/Server/Server.hpp"

// Consts
#define BUFFER_SIZE (1024 * 1024) // 1MB
#define STATIC_HTTP "static/http/"
#define STATIC_404 "static/404/index.html"
#define CLIENTS_COUNT 10
#define RESET_COLOR "\033[0m"
#define BLUE_TEXT "\033[1;34m"
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"

// Function prototypes
void ft_handle_client(int client_fd);
std::string buildHttpResponse(std::string __unused &method, std::string &target);
void parse_request(const std::string &request, std::string &method, std::string &target);
int CreateServerSocket();
int waitClients(int serverSocket);

// global variables

#endif