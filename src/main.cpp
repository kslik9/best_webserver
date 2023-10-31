/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:34:53 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/31 20:36:25 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int main(int __unused argc, char const __unused *argv[])
{
    // ------------------------------------------------------------------------------------------------
    int port = 8080;
    // ------------------------------------------------------------------------------------------------
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // ------------------------------------------------------------------------------------------------
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Error binding socket" << std::endl;
        close(server_socket);
        return 1;
    }
    // ------------------------------------------------------------------------------------------------
    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "Error listening on socket" << std::endl;
        close(server_socket);
        return 1;
    }
    // ------------------------------------------------------------------------------------------------
    std::cout << "Server is listening on 0.0.0.0:" << port << std::endl;
    // ------------------------------------------------------------------------------------------------
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
    // ------------------------------------------------------------------------------------------------
    return 0;
}
