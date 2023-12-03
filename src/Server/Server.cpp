#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server(const Server &src) : config(src.config)
{
}

Server::Server(Config &config) : config(config)
{
	std::cout << "Config loaded at the server" << std::endl;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Server &Server::operator=(Server const &rhs)
{
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	setNonBlocking(int socketFd) {
	int flags = fcntl(socketFd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(socketFd, F_SETFL, flags);
}


#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

void	Server::setServerAddress(unsigned short &port, std::string &hostName) {
	std::cout << "port: " << port << " hostname: " << hostName << std::endl;
	// memset((char *)&this->serverAddress, 0, sizeof(this->serverAddress));
	// this->serverAddress.sin_family = AF_INET;
	// this->serverAddress.sin_port = htons(port);
	// addrinfo *result;
	// addrinfo exp;
	// getaddrinfo(hostName, port, &exp, &result);
	// this->serverAddress.sin_addr = 0;
	// in_addr_t ip = inet_addr(hostName.c_str());
	// if (ip == INADDR_NONE) {
	// 	std::cerr << "Invalid Ip Address " << hostName << std::endl;
	// }
	// this->serverAddress.sin_addr.s_addr = ip;
	
	
}

void Server::start() {
	int	serverSocketFd;
	unsigned short	port;
	std::string hostName;
	std::set<std::string>::iterator portsIt;
	struct hostent *hostnm;
	struct sockaddr_in server;
	int opt = 1;

	// hostnm = gethostbyname();

	for (int i = 0; i < config.srvConf.size(); i++) {
		portsIt = config.srvConf[i].ports.begin();
		for (portsIt = config.srvConf[i].ports.begin(); portsIt != config.srvConf[i].ports.end(); portsIt++) {


			// this->portsAndHosts.insert(std::make_pair(*portsIt, config.srvConf[i].host));
			port = std::stoi(*portsIt);
			hostName = config.srvConf[i].host;
			this->serverSocketsFd.push_back(socket(AF_INET, SOCK_STREAM, 0));
			if (this->serverSocketsFd[i] < 0) {
				logger.Log(ERROR, "Error creating server socket");
				throw std::runtime_error("Error creating server socket");
			}

			// 	//setnonblocking
			setNonBlocking(this->serverSocketsFd[i]);

			// this solves the error of binding by reusing address
			if (setsockopt(this->serverSocketsFd[i], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
				logger.Log(ERROR, "Error of binding by reusing address");
				throw std::runtime_error("Error of binding by reusing address");
			}

			// binding socket with address server_name on a port
			setServerAddress(port, hostName);
			continue;

			if (bind(this->serverSocketsFd[i], (struct sockaddr *)&this->serverAddress, sizeof(this->serverAddress)) < 0) {
				logger.Log(ERROR, "Error binding server socket");
				throw std::runtime_error("Error binding server socket");
			}

			// listen for incoming connections
			if (listen(this->serverSocketsFd[i], CLIENTS_COUNT) < 0) {
				logger.Log(ERROR, "Error listening on socket");
				throw std::runtime_error("Error listening on socket");
			}
			std::cout << GREEN_TEXT << "server listening on port " << port << RESET_COLOR << std::endl;
		}
	}
}

void Server::waitClients()
{
	int closeConnection;
	std::vector<struct pollfd> fds;
	int rc;
	int endServer = false;
	int clientSd = -1;
	struct pollfd tempPollFd;

	//init pollfds fds with server sockets
	for (int i = 0; i < this->serverSocketsFd.size(); i++) {
		tempPollFd.fd = serverSocketsFd[i];
		tempPollFd.events = POLLIN;
		fds.push_back(tempPollFd);
	}


	while (endServer == false) {
		rc = poll(&fds[0], fds.size(), 3000);
		if (rc < 0) {
			std::cout << "poll() error\n";
		}
		for (int i = 0; i < fds.size(); i++) {
			//loop to find descriptors that return POLLIN
			//then determine if it's listening or active connection
			if (fds[i].revents == 0)
				continue;
			if (fds[i].revents != POLLIN) {
				std::cout << "revents error\n";
				endServer = true;
				break;
			}

			if (std::find(this->serverSocketsFd.begin(), this->serverSocketsFd.end(), fds[i].fd) != this->serverSocketsFd.end())
			{
				//this is a listening socket and it's redable
					struct sockaddr_in client_addr;
					socklen_t client_addr_len = sizeof(client_addr);
					clientSd = accept(fds[i].fd, (struct sockaddr *)&client_addr, &client_addr_len);
					if (clientSd < 0)
					{
						std::cerr << "accept() failed\n";
						endServer = true;
						break;
					}
					//add new incoming connection to the pollfd
					std::cout << "new incoming connection " << clientSd << std::endl;
					tempPollFd.fd = clientSd;
					tempPollFd.events = POLLIN;
					fds.push_back(tempPollFd);
			}

			//not a listening socket and it's readable
			else {
				std::cout << "fd " << fds[i].fd << " is readable" << std::endl;
				closeConnection = false;
				while (true) {
					char *buffer = new char[BUFFER_SIZE];
					ssize_t bytesReceived = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
					if (bytesReceived < 0) {
						std::cout << "recv() failed\n";
						closeConnection = true;
						break;
					}
					if (bytesReceived == 0) {
						std::cout << "connection closed\n";
						closeConnection = true;
						delete[] buffer;
						break;
					}
					std::cout << "bytes received: " << bytesReceived << std::endl;

					std::string str_buffer(buffer);
					std::string http_resp = buildHttpResponse(str_buffer);
					//send response to client
					rc = send(fds[i].fd, http_resp.c_str(), http_resp.length(), 0);
					if (rc < 0) {
						std::cerr << "send() failed\n";
						closeConnection = true;
						break;
					}
					// close(fds[i].fd);
					closeConnection = true;
					delete[] buffer;
				}
				if (closeConnection) {
					close(fds[i].fd);
					fds[i].fd = -1;
				}
			}
		}
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


Config Server::getConfig() const {
	return this->config;
}

sockaddr_in Server::getServer_address() const {
	return this->serverAddress;
}

/* ************************************************************************** */