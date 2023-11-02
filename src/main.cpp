#include "webserv.hpp"

const char *sIp = "192.168.1.100";

int main(int __unused argc, char const __unused *argv[])
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return (EXIT_FAILURE);
    }
    // --------------------------------------------------------------
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // server_address.sin_addr.s_addr = inet_addr("0.0.0.0");   ----  inet_addr converts ip address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Error binding socket" << std::endl;
        close(server_socket);
        return (EXIT_FAILURE);
    }
    // --------------------------------------------------------------
    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "Error listening on socket" << std::endl;
        close(server_socket);
        return (EXIT_FAILURE);
    }
    std::cout << "Server is listening on 0.0.0.0:8080" << std::endl;
    // --------------------------------------------------------------
    while (1)
    {
        sockaddr *client_addrr = new sockaddr();
        socklen_t *client_addrr_len = new socklen_t();
        *client_addrr_len = sizeof(*client_addrr);
        int client_fd = accept(server_socket, client_addrr, client_addrr_len);
        ft_handle_client(client_fd);
        delete client_addrr;
        delete client_addrr_len;
    }
    // --------------------------------------------------------------
    return 0;
}
