// #ifndef "WEBSERV_HPP"
// #define "WEBSERV_HPP"

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

// Consts
#define BUFFER_SIZE (1024 * 1024) // 1MB

// Function prototypes
void ft_handle_client(int client_fd);
std::string buildHttpResponse(std::string &method, std::string &target);
