/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:33:48 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/31 19:41:52 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        std::string req = ("curl -X GET " + static_cast<std::string>(argv[1]));
        std::cout << "Client tried: " << req << std::endl;
        if (system(req.c_str()) == -1)
            std::cout << "An error occurred during the request" << std::endl;
    }
    return 0;
}
