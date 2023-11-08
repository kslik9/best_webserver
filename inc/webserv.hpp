#pragma once

// IO
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <memory>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string>
#include <map>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <poll.h>

// Consts
#define BUFFER_SIZE (1024 * 1024) // 1MB

#define STATIC_HTTP "static/http/"
#define STATIC_404 "static/404/index.html"

#define CLIENTS_COUNT 2

// Function prototypes
void ft_handle_client(int client_fd);
std::string buildHttpResponse(std::string __unused &method, std::string &target);
void parse_request(const std::string &request, std::string &method, std::string &target);
int CreateServerSocket();
int waitClients(int serverSocket);