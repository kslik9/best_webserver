/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:12:06 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/31 21:48:16 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void ft_handle_client(int client_fd)
{
    if (client_fd >= 0)
    {
        char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
        std::cout << "Client Connected, fd = " << client_fd << std::endl;
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0)
        {
            std::cout << buffer << std::endl;
        }
        else
            std::cout << "Less than 0" << std::endl;
    }
}
