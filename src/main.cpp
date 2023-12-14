#include "webserv.hpp"

Logger logger = Logger("webserv.log");

int main(int argc, char const *argv[])
{
    std::string conf_file("configs/webserver_1server.conf");
    if (argc > 1)
        conf_file = argv[1];
    Config config(conf_file);
    Server server;
    try
    {
        server.start(config);
        while (true)
        {
            try
            {
                server.waitClients();
            }
            catch (const std::exception &e)
            {
                std::cerr << "Can't wait Clients: " << e.what() << '\n';
                continue;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Can't start Server: " << e.what() << '\n';
        exit(1);
    }
    return 0;
}
