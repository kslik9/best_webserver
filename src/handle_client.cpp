/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by    #+#            #+#    #+#             */
/*   Updated: 2023/11/02 00:43:10 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

std::string pars_method(std::string &buffer, int &pos)
{
    return (buffer.substr(0, pos));
}
std::string pars_target(std::string &buffer, int &pos)
{
    int i = (pos + 1);
    std::string target;
    while (buffer[i] != ' ')
        target += buffer[i++];
    target = target.substr(1, target.length() - 1);
    return (target);
}

void ft_handle_client(int client_fd)
{
    if (client_fd >= 0)
    {
        char *buffer = new char[BUFFER_SIZE];
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0)
        {
            std::string str_buffer(buffer), target, method;
            int pos = str_buffer.find(" ");
            method = pars_method(str_buffer, pos);
            target = pars_target(str_buffer, pos);
            // ------------------------------------------------------------------------------------------------
            std::string http_resp = buildHttpResponse(method, target);
            send(client_fd, http_resp.c_str(), http_resp.length(), 0);
            // ------------------------------------------------------------------------------------------------
            close(client_fd);
        }
        delete[] buffer;
    }
}
