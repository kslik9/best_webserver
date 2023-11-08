
#include "webserv.hpp"

#include "string.h"



int main() {
    

    int addrlen;

    int maxClients = 30;
    
    int i;
    int valRead;
    
    

    //initialise all client sockets to 0
    int clientSocket[30];
    for (int i = 0; i < maxClients; i++)
        clientSocket[i] = 0;

    //create server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("socket failed");
        exit(1);
    }

    // -----------------------------------------------------------------------
    // this solves the error of binding by reusing address 
    int opt = true;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit (EXIT_FAILURE);
    }
    // -----------------------------------------------------------------------
    // -----------------------------------------------------------------------
    //bind the server socket
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error binding socket\n";
        close(serverSocket);
        exit (EXIT_FAILURE);
    }
    // -----------------------------------------------------------------------
    // -----------------------------------------------------------------------
    //Listen on 0.0.0.0:8000
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening on socket\n";
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    std::cout << "Server is listening on 0.0.0.0:8080\n";
    // -----------------------------------------------------------------------
    //Accept the incoming connections
    char buffer[1025];
        //message
    std::string message = "afin azzin\r\n";
        //set of socket descriptors
    fd_set  readFds;
    int maxFd;
    int fd;
    int activity;
    int newSocket;
    int addrLen = sizeof(server_address);
    std::cout << "waiting for connection\n";
    while (true) {
        //clear the socket set
        FD_ZERO(&readFds);
        
        //add server socket to set
        FD_SET(serverSocket, &readFds);
        maxFd = serverSocket;

        //add child sockets to set
        for (int i = 0; i < maxClients; i++) {
            //socket descriptor
            fd = clientSocket[i];

            //if valid socket descriptor then add to read list
            if (fd > 0)
                FD_SET(fd, &readFds);
            if (fd > maxFd)
                maxFd = fd;
        }

        //wait for any activity on one of the sockets which are set to the list
        activity = select(maxFd + 1, &readFds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("select error");
            exit(EXIT_FAILURE);
        }

        //this checks if is there any incoming connection, by checking if anything happened in the serverSocket
        if (FD_ISSET(serverSocket, &readFds)) {
            int newSocket = accept(serverSocket, (struct sockaddr*)&server_address, (socklen_t*)&addrLen);
            if (newSocket < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            std::cout << "new connection, socket fd is "
                    << newSocket
                    << ", ip is : "
                    << inet_ntoa(server_address.sin_addr)
                    << ":"
                    << ntohs  (server_address.sin_port)
                    << std::endl;
            
            // send(newSocket, message.data(), strlen((char *)message.data()), 0);
            ft_handle_client(newSocket);
            std::cout << "message sent successfully\n";

            //add new socket to array of sockets
            for (int i = 0; i < maxClients; i++) {
                if (clientSocket[i] == 0) {
                    clientSocket[i] = newSocket;
                    std::cout << "added to list of sockets on " << i << std::endl;
                    break;
                }
            }
        }

        int valRead;
        for (int i = 0; i < maxClients; i++) {
            fd = clientSocket[i];
            if (FD_ISSET(fd, &readFds)) {
                if ((valRead = read(fd, buffer, 1024))) {
                    //Somebody disconnected , get his details and print  
                    getpeername(fd , (struct sockaddr*)&server_address , (socklen_t*)&addrLen);   
                    printf("Host disconnected , ip %s , port %d \n" ,  
                          inet_ntoa(server_address.sin_addr) , ntohs(server_address.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close( fd );   
                    clientSocket[i] = 0; 
                }
                else {  
                    ft_handle_client(fd);
                }
            }
        }
    
    }
    







    // -----------------------------------------------------------------------
    
}




// int main(int argc, char const *argv[])
// {
//     int opt = 1;
//     int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (serverSocket == -1)
//     {
//         std::cerr << "Error creating socket" << '\n';
//         return EXIT_FAILURE;
//     }
//     // -----------------------------------------------------
//     // this solves the error of binding by reusing address 
//     if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
//         perror("setsockopt");
//         exit(1);
//     }
//     // -----------------------------------------------------
//     sockaddr_in server_address;
//     server_address.sin_family = AF_INET;
//     server_address.sin_port = htons(8080);
//     server_address.sin_addr.s_addr = INADDR_ANY;
//     if (bind(serverSocket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
//     {
//         std::cerr << "Error binding socket" << '\n';
//         close(serverSocket);
//         return EXIT_FAILURE;
//     }
//     // -----------------------------------------------------
//     if (listen(serverSocket, 5) == -1)
//     {
//         std::cerr << "Error listening on socket" << '\n';
//         close(serverSocket);
//         return EXIT_FAILURE;
//     }
//     // -----------------------------------------------------
//     std::cout << "Server is listening on 0.0.0.0:8080" << '\n';
//     // -----------------------------------------------------
//     fd_set read_fds;
//     int max_fd = serverSocket;
//     struct timeval time;
//     time.tv_sec = 3;
//     time.tv_usec = 0;
//     while(1) {
//         FD_ZERO(&read_fds);
//         FD_SET(serverSocket, &read_fds);

//         int s = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
//         if (s < 0) {
//             perror("select");
//             exit(1);
//         }
//         else if (FD_ISSET(serverSocket, &read_fds)) {
//             sockaddr client_addr;
//             socklen_t client_addr_len = sizeof(client_addr);
//             int client_fd = accept(serverSocket, &client_addr, &client_addr_len);
//             if (client_fd < 0)
//             {
//                 perror("accept");
//                 exit(1);
//             }
//             FD_SET(client_fd, &read_fds);
//             if (client_fd > max_fd)
//                 max_fd = client_fd;
//             ft_handle_client(client_fd);
//         }
//         // std::cout << max_fd << std::endl;
//     }




    // while (1)
    // {
    //     sockaddr client_addr;
    //     socklen_t client_addr_len = sizeof(client_addr);
    //     int client_fd = accept(serverSocket, &client_addr, &client_addr_len);
    //     if (client_fd < 0)
    //     {
    //         perror("accept");
    //         return EXIT_FAILURE;
    //     }
    //     ft_handle_client(client_fd);
    // }
    // -----------------------------------------------------
//     return 0;
// }
