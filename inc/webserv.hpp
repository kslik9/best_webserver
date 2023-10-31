/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:36:24 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/31 19:17:48 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// IO
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


// function prototypes
void ft_handle_client(int client_fd);
