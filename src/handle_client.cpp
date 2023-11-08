
#include "webserv.hpp"

// void parse_request(const std::string &request, std::string &method, std::string &target)
// {
//     try
//     {
//         std::istringstream iss(request);
//         iss >> method >> target;
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//         method = "GET";
//         target = "/";
//     }
// }


// void ft_handle_client(int client_fd)
// {
//     if (client_fd >= 0)
//     {
//         // -----------------------------------------------------
//         char *buffer = new char[BUFFER_SIZE];
//         ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);

        
//         // std::cout << "--------[" << buffer << "]--------\n";
//         // -----------------------------------------------------
//         if (bytes_received > 0)
//         {
//             // -----------------------------------------------------
//             std::string str_buffer(buffer), target, method;
//             int pos = str_buffer.find(" ");
//             // -----------------------------------------------------
//             parse_request(str_buffer, method, target);
//             // -----------------------------------------------------
//             std::string http_resp = buildHttpResponse(method, target);
//             send(client_fd, http_resp.c_str(), http_resp.length(), 0);
//             // -----------------------------------------------------
//             close(client_fd);
//         }
//         delete[] buffer;
//     }
// }

