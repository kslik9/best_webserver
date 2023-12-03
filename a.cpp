#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include<stdio.h>
#include<netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    const char *dom = "localhost";
    struct addrinfo hints, *res, *p;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(dom, nullptr, &hints, &res) != 0) {
        std::cout << "error\n";
        exit(0);
    }

    // for (p = res; p != nullptr; p = p->ai_next) {
        p = res;
        std::cout << "lo\n";
        void *addr;
        char ipstr[INET6_ADDRSTRLEN];

        struct sockaddr_in *ip = reinterpret_cast<struct sockaddr_in*>(p->ai_addr);
        addr = &(ip->sin_addr);

        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        std::cout << "IP Address: " << ipstr << std::endl;
    // }


}