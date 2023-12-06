#include "Server.hpp"
#include <cerrno>
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server() {

}




/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server() {
	conf.clear();
	serverSocketsFd.clear();
	portsAndHosts.clear();
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


void	Server::setServerAddress(unsigned short &port, std::string &hostName) {
	struct addrinfo hints;
	struct addrinfo *res;
	struct addrinfo *p;
	const char *portCharPtr = std::to_string(port).c_str();

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(hostName.c_str(), portCharPtr, &hints, &res) != 0) {
		std::cout << "getaddrinfo() error" << std::endl;
		return;
	}
	
	struct sockaddr_in *ip = reinterpret_cast<struct sockaddr_in*>(res->ai_addr);

	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_port = htons(port);
	this->serverAddress.sin_addr = ip->sin_addr;

	freeaddrinfo(res);
}

void Server::start(Config &mainConf) {
	int	serverSocketFd;
	unsigned short	port;
	std::string hostName;
	std::set<int>::iterator portsIt;
	struct hostent *hostnm;
	struct sockaddr_in server;
	int opt = 1;
	int socketIndex = 0;

	for (int i = 0; i < mainConf.how_mn_servers(); i++) {
		// std::cout << "conf: " << mainConf.srvConf.at(i).name << std::endl;
		for (portsIt = mainConf.srvConf[i].ports.begin(); portsIt != mainConf.srvConf[i].ports.end(); portsIt++) {
			port = *portsIt;
			hostName = mainConf.srvConf[i].name;
			
			int opt = 1;
			this->serverSocketsFd.push_back(socket(AF_INET, SOCK_STREAM, 0));
			if (this->serverSocketsFd[socketIndex] < 0) {
				perror("socket() failed");
				exit(EXIT_FAILURE);
			}

			//setnonblocking
			setNonBlocking(this->serverSocketsFd[socketIndex]);

			
			if (this->serverSocketsFd[i] < 0) {
				logger.Log(ERROR, "Error creating server socket");
				throw std::runtime_error("Error creating server socket");
			}

			// this solves the error of binding by reusing address
			if (setsockopt(this->serverSocketsFd[socketIndex], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
			logger.Log(ERROR, "Error of binding by reusing address");
			throw std::runtime_error("Error of binding by reusing address");
			}

			//set server address info
			setServerAddress(port, hostName);

			//bind socket
			if (bind(this->serverSocketsFd[socketIndex], (struct sockaddr *)&this->serverAddress, sizeof(this->serverAddress)) < 0)
			{
				logger.Log(ERROR, "Error binding server socket");
				throw std::runtime_error("Error binding server socket");
			}

			// listen on
			if (listen(this->serverSocketsFd[socketIndex], CLIENTS_COUNT) < 0)
			{
				logger.Log(ERROR, "Error listening on socket");
				throw std::runtime_error("Error listening on socket port " + std::to_string(port));
			}

			//include serv conf to each socket
			conf.push_back(mainConf.srvConf[i]);

			// -----------------------------------------------------
			std::cout << GREEN_TEXT << "Server is listening on "
					<< hostName
					<< ":" << port << RESET_COLOR << std::endl;

			socketIndex++;
		}
	}
}

void Server::waitClients()
{
	int closeConnection;
	std::vector<struct pollfd> fds;
	int rc;
	struct pollfd 	tempPollFd;
	int				currentPortInex;
	int endServer = false;
	int clientSd = -1;

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
			// if (fds[i].revents != POLLIN) {
			// 	std::cout << "revents error\n";
			// 	endServer = true;
			// 	break;
			// }

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
				// setNonBlocking(clientSd);
				tempPollFd.fd = clientSd;
				tempPollFd.events = POLLIN;
				fds.push_back(tempPollFd);

				currentPortInex =  i;
			}

			// if (pollfd[i].revents & POLLOUT)
			//not a listening socket and it's readable
			else {
				std::cout << "fd " << fds[i].fd << " is readable" << std::endl;
				closeConnection = false;
				while (true) {
					char *buffer = new char[BUFFER_SIZE];
					ssize_t bytesReceived = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
					if (bytesReceived < 0) {
						// std::cout << "recv() failed\n";
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
					std::string http_resp = buildHttpResponse(currentPortInex, str_buffer);
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


sockaddr_in Server::getServer_address() const {
	return this->serverAddress;
}

/* ************************************************************************** */