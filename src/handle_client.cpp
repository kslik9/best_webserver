/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:12:06 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/31 19:25:00 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void ft_handle_client(int client_fd)
{
    if (client_fd >= 0)
    {
        std::cout << "Client Connected" << std::endl;
    }
}