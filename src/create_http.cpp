/* ************************************************************************** */
/*                                                                            */
/*                                  :::      ::::::::                         */
/*                                :+:      :+:    :+:                         */
/*                              +:+ +:+         +:+                           */
/*                            +#+  +:+       +#+                              */
/*                          +#+#+#+#+#+   +#+                                 */
/*                               #+#    #+#                                   */
/*                              ###   ########.fr                             */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/webserv.hpp"

std::string buildHttpResponse(std::string &method, std::string &target)
{
    // Build the HTTP header
    std::stringstream headerStream;
    headerStream << "HTTP/1.1 200 OK\r\n"
                 << "Content-Type: text/plain\r\n"
                 << "\r\n"
                 << "Method: " << method << "\n"
                 << "Target: " << target << "\n";

    // Return the response
    return (headerStream.str());
}
