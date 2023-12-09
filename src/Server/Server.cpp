#include "Server.hpp"
#include <cerrno>
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

class Socket {
	private:
		int										contentLen;
		int										bodySize;
	public:
		void	setContentLen(std::string bufferStr);
		void	setBodySize(std::string bufferStr, int bytesReceived);
};


Server::Server() {
	this->contentLen = -2;
	this->bodySize = 0;
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
	// this->serverAddress.sin_addr = ip->sin_addr;
	this->serverAddress.sin_addr.s_addr = INADDR_ANY;

	freeaddrinfo(res);
}

void Server::start(Config &mainConf) {
	int						serverSocketFd;
	unsigned short			port;
	std::string				hostName;
	std::set<int>::iterator	portsIt;
	struct hostent			*hostnm;
	struct sockaddr_in		server;
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


int getContentLen(std::string bufferStr) {
	std::string target = "Content-Length: ";

    size_t found = bufferStr.find(target);

    if (found != std::string::npos) {
        found += target.length();
        size_t end = bufferStr.find("\r\n", found);
        std::string lengthStr = bufferStr.substr(found, end - found);

        // Convert string to integer
		// std::cout << "len::: " << lengthStr << "\n";
        int contentLength = std::stoi(lengthStr);
        return contentLength;
    }
	return -1;
}

int countBodySize(std::string bufferStr, int bytesReceived) {
	if (bytesReceived < 0)
		return 0;
	int foundbrbn = bufferStr.find("\r\n\r\n");

	// std::cout << "shoko: " << bufferStr << std::endl;
	if (bufferStr.find("\r\n\r\n") != std::string::npos) {
		// std::cout << "ki: [[" << bufferStr.substr(foundbrbn + 4) << "]\n";
		std::cout << "found\n";
		return bytesReceived - (foundbrbn + 4);
	}
	return bytesReceived;
}

bool Server::reachedTheEnd(std::string bufferStr, int bytesReceived) {
	
	if (this->bodySize >= this->contentLen)
		return true;
	return false;
}

void Server::waitClients()
{
	bool	closeConnection;
	std::vector<struct pollfd>	fds;
	int							rc;
	struct pollfd				tempPollFd;
	int							currentPortInex;
	int endServer = false;
	int clientSd = -1;
	std::string http_resp;


	//init pollfds fds with server sockets
	for (int i = 0; i < this->serverSocketsFd.size(); i++) {
		tempPollFd.fd = serverSocketsFd[i];
		tempPollFd.events = POLLIN;
		fds.push_back(tempPollFd);
	}

	while (endServer == false) {
		closeConnection = false;
		rc = poll(&fds[0], fds.size(), 3000);
		if (rc < 0) {
			std::cout << "poll() error\n";
			break;
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
				// setNonBlocking(clientSd);
				tempPollFd.fd = clientSd;
				tempPollFd.events = POLLIN;
				fds.push_back(tempPollFd);
				currentPortInex =  i;
			}

			// if (pollfd[i].revents & POLLOUT)
			//not a listening socket and it's readable
			else {
				std::cout << "fd " << fds[i].fd << " is readable, i: " << i << std::endl;
				// char	buffer[BUFFER_SIZE];
				char buffer[BUFFER_SIZE];
				std::string receivedData;

				closeConnection = false;
				ssize_t bytesReceived;
				std::string joinedStr;
				this->contentLen = -2;
				this->bodySize = 0; 
				while(true) {
					memset(buffer, '\0', BUFFER_SIZE);
					bytesReceived = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
					std::string bufferStr(buffer);
					setContentLen(bufferStr);
					setBodySize(bufferStr, bytesReceived);
					if (bytesReceived < 0) {
						if (reachedTheEnd(bufferStr, bytesReceived)) {
							closeConnection = true;
							joinedStr.append(bufferStr);
							break;
						}
						// std::cout << "con_len: " << this->contentLen << std::endl;
						// std::cout << "vody_si: " << buffer << std::endl;
						continue;
					}
					if (bytesReceived == 0) {
						joinedStr.append(bufferStr);
						closeConnection = true;
						break;
					}
					if (reachedTheEnd(bufferStr, bytesReceived)) {
						closeConnection = true;
						joinedStr.append(bufferStr);
						break;
					}
					std::cout << RED_TEXT << "part: " << bufferStr << RESET_COLOR << "\n";
					joinedStr.append(bufferStr);
					// memset(buffer, '\0', BUFFER_SIZE);
					std::cout << "inside while\n";
					// std::cout << "con_len: " << this->contentLen << std::endl;
					// std::cout << "vody_si: " << this->bodySize << std::endl;
				}

				std::cout << "con_len: " << this->contentLen << std::endl;
				std::cout << "vody_si: " << this->bodySize << std::endl;
				// exit(1);
				// delete[] buffer;
				if (!joinedStr.empty()) {
					std::cout << "na\n";
					closeConnection = true;
					// std::string str_buffer(buffer);
					// data_read(str_buffer, bytesReceived);
					http_resp = buildHttpResponse(currentPortInex, joinedStr);
					// http_resp = buildHttpResponse(currentPortInex, buffer);
					//send response to client
					std::cout << "http_res: " << http_resp << std::endl;
					rc = send(fds[i].fd, http_resp.c_str(), http_resp.length(), 0);
					std::cout << "fd: " << fds[i].fd << " i: " << i << std::endl;
					if (rc < 0) {
						std::cerr << "send() failed\n";
						closeConnection = true;
						break;
					}
					// closeConnection = true;
				}
					// close(fds[i].fd);
					// delete[] buffer;
			std::cout << "con: " << closeConnection << std::endl;
			std::cout << "sent: \n";
			if (closeConnection == true) {
				std::cout << "fd " << fds[i].fd << " closed, index: " << i << " fds size: " << fds.size() << std::endl;
				close(fds[i].fd);
				fds[i].fd = -1;
				fds.erase(fds.begin() + i);
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

void	Server::setContentLen(std::string bufferStr) {
	if (this->contentLen == -2)
		this->contentLen = getContentLen(bufferStr);
}

void	Server::setBodySize(std::string bufferStr, int bytesReceived) {
	this->bodySize += countBodySize(bufferStr, bytesReceived);
}
/* ************************************************************************** */