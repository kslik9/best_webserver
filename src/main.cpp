
#include "webserv.hpp"

int main(int argc, char const *argv[])
{
    //thist create server socket
    int serverSocket = CreateServerSocket();

    //handle connections from clients
    waitClients(serverSocket);
    close(serverSocket);
    return 0;
}
