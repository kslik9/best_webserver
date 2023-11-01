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
