#include "webserv.hpp"

Logger logger = Logger("webserv.log");

int main(int argc, char const *argv[])
{
    try
    {
        if (argc != 2)
        {
            logger.Log(ERROR, "bad arguments");
            logger.Log(INFO, "try: ./webserv ./webserver.conf");
            return 1;
        }
        Server server;
        Config config(argv[1]);
        Session session(server, config);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    // -----------------------------------------------------
    // thist create server socket
    int serverSocket = CreateServerSocket();
    // handle connections from clients
    waitClients(serverSocket);
    close(serverSocket);
    return 0;
}
