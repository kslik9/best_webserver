/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:34:53 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/31 15:20:53 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int main(int argc, char const *argv[])
{
    // ------------------------------------------------------------------------------------------------
    int port = 8080;
    // ------------------------------------------------------------------------------------------------
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    // ------------------------------------------------------------------------------------------------
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return 1;
    }
    // ------------------------------------------------------------------------------------------------
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Error listening on socket" << std::endl;
        close(serverSocket);
        return 1;
    }
    // ------------------------------------------------------------------------------------------------
    std::cout << "Server is listening on port: " << port << "..." << std::endl;
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientSocket == -1)
    {
        std::cerr << "Error accepting client connection" << std::endl;
        close(serverSocket);
        return 1;
    }
    // ------------------------------------------------------------------------------------------------
    std::cout << "Client connected" << std::endl;
    close(clientSocket);
    close(serverSocket);
    // ------------------------------------------------------------------------------------------------
    return 0;
}
