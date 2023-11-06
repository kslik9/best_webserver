
#include "webserv.hpp"


int main(int argc, char const *argv[])
{
    int opt = 1;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Error creating socket" << '\n';
        return EXIT_FAILURE;
    }
    // -----------------------------------------------------
    // this solves the error of binding by reusing address 
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(1);
    }
    // -----------------------------------------------------
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Error binding socket" << '\n';
        close(server_socket);
        return EXIT_FAILURE;
    }
    // -----------------------------------------------------
    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "Error listening on socket" << '\n';
        close(server_socket);
        return EXIT_FAILURE;
    }
    // -----------------------------------------------------
    std::cout << "Server is listening on 0.0.0.0:8080" << '\n';
    // -----------------------------------------------------
    fd_set read_fds;
    int max_fd = server_socket;
    struct timeval time;
    time.tv_sec = 3;
    time.tv_usec = 0;
    while(1) {
        FD_ZERO(&read_fds);
        FD_SET(server_socket, &read_fds);

        int s = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (s < 0) {
            perror("select");
            exit(1);
        }
        else if (FD_ISSET(server_socket, &read_fds)) {
            sockaddr client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int client_fd = accept(server_socket, &client_addr, &client_addr_len);
            if (client_fd < 0)
            {
                perror("accept");
                exit(1);
            }
            FD_SET(client_fd, &read_fds);
            if (client_fd > max_fd)
                max_fd = client_fd;
            ft_handle_client(client_fd);
        }
        // std::cout << max_fd << std::endl;
    }








    // while (1)
    // {
    //     sockaddr client_addr;
    //     socklen_t client_addr_len = sizeof(client_addr);
    //     int client_fd = accept(server_socket, &client_addr, &client_addr_len);
    //     if (client_fd < 0)
    //     {
    //         perror("accept");
    //         return EXIT_FAILURE;
    //     }
    //     ft_handle_client(client_fd);
    // }
    // -----------------------------------------------------
    return 0;
}
