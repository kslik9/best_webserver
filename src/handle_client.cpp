/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by    #+#            #+#    #+#             */
/*   Updated: 2023/11/02 00:39:40 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void ft_handle_client(int client_fd)
{
    if (client_fd >= 0)
    {
        // char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
        char *buffer = new char[BUFFER_SIZE];
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0)
        {
            std::string str_buffer(buffer), target;
            int pos = str_buffer.find(" ");
            int i = (pos + 1);
            std::string method = str_buffer.substr(0, pos);
            while (str_buffer[i] != ' ')
                target += str_buffer[i++];
            std::cout << "method: " << method << std::endl;
            std::cout << "target: " << target << std::endl;
            std::cout << "-------------------" << std::endl;
            // ------------------------------------------------------------------------------------------------
            std::string http_resp = buildHttpResponse(method, target);
            send(client_fd, http_resp.c_str(), http_resp.length(), 0);
            // ------------------------------------------------------------------------------------------------
            close(client_fd);
        }
    }
}
