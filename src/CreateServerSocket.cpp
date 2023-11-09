
#include "webserv.hpp"

int CreateServerSocket()
{
    int opt = 1;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket\n";
        exit(EXIT_FAILURE);
    }
    // -----------------------------------------------------
    // this solves the error of binding by reusing address
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    // -----------------------------------------------------
    // binding socket with address 0.0.0.0:8080
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Error binding socket\n";
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    // -----------------------------------------------------
    // listen on 0.0.0.0:8080
    if (listen(serverSocket, CLIENTS_COUNT) == -1)
    {
        std::cerr << "Error listening on socket\n";
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    // -----------------------------------------------------
    std::cout << "Server is listening on 0.0.0.0:8080\n";
    // -----------------------------------------------------
    return serverSocket;
}
