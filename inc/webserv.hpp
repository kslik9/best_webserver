/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:36:24 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/31 21:44:48 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef "WEBSERV_HPP"
// #define "WEBSERV_HPP"

// IO
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Consts
#define BUFFER_SIZE (1024 * 1024) // 1MB

// Function prototypes
void ft_handle_client(int client_fd);
