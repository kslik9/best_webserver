
#include "webserv.hpp"

int activeClients = 0;

void parse_request(const std::string &request, std::string &method, std::string &target)
{
    try
    {
        std::istringstream iss(request);
        iss >> method >> target;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        method = "GET";
        target = "/";
    }
}

int waitClients(int serverSocket)
{
    struct pollfd fds[CLIENTS_COUNT + 1];
    fds[0].fd = serverSocket;
    fds[0].events = POLLIN | POLLPRI;
    int activeClients = 0;
    // -----------------------------------------------------
    // fill all fds with 0
    for (int i = 1; i < CLIENTS_COUNT; i++)
        fds[i].fd = 0;
    // -----------------------------------------------------
    while (true)
    {
        int activity = poll(fds, activeClients + 1, 5000);
        if (activity < -1)
            std::cout << "Error : L:36" << std::endl;
        else
        {
            // check if a client tryin to connect and add it to pollfd list
            if (fds[0].revents & POLLIN)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int clientSocket = accept(serverSocket, (struct sockaddr *)&client_addr, &client_addr_len);
                for (int i = 1; i < CLIENTS_COUNT; i++)
                {
                    if (fds[i].fd == 0)
                    {
                        fds[i].fd = clientSocket;
                        fds[i].events = POLLIN | POLLPRI;
                        activeClients++;
                        std::cout << "new connection!! socket fd is " << clientSocket << " - " << inet_ntoa(client_addr.sin_addr) << std::endl;
                        break;
                    }
                }
            }
            // check data from clients
            for (int i = 1; i < CLIENTS_COUNT; i++)
            {
                if (fds[i].fd > 0 && (fds[i].revents & POLLIN))
                {
                    char *buffer = new char[BUFFER_SIZE];
                    ssize_t bytes_received = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
                    if (bytes_received < 0 || bytes_received == 0)
                    {
                        close(fds[i].fd);
                        fds[i].fd = 0;
                        fds[i].events = 0;
                        fds[i].revents = 0;
                        activeClients--;
                        std::cout << "fd " << fds[i].fd << " removed\n";
                    }
                    else
                    {
                        std::string str_buffer(buffer), target, method;
                        int pos = str_buffer.find(" ");
                        // -----------------------------------------------------
                        parse_request(str_buffer, method, target);
                        // -----------------------------------------------------
                        std::string http_resp = buildHttpResponse(method, target);
                        send(fds[i].fd, http_resp.c_str(), http_resp.length(), 0);
                        close(fds[i].fd);
                    }
                }
            }
        }
    }
}