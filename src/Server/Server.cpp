#include "Server.hpp"
#include <cerrno>
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server()
{
	this->contentLen = -2;
	this->bodySize = 0;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
	conf.clear();
	sockets.clear();
	serverSocketsFd.clear();
	portsAndHosts.clear();
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Server &Server::operator=(Server const &rhs)
{
	this->serverAddress = rhs.serverAddress;
	this->serverSocketsFd = rhs.serverSocketsFd;
	this->portsAndHosts = rhs.portsAndHosts;
	this->conf = rhs.conf;
	this->contentLen = rhs.contentLen;
	this->bodySize = rhs.bodySize;
	this->sockets = rhs.sockets;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void setNonBlocking(int socketFd)
{
	int flags = fcntl(socketFd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(socketFd, F_SETFL, flags);
}

void Server::setServerAddress(unsigned short &port, std::string &hostName)
{
	struct addrinfo hints;
	struct addrinfo *res;
	const char *portCharPtr = std::to_string(port).c_str();

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(hostName.c_str(), portCharPtr, &hints, &res) != 0)
	{
		std::cout << "getaddrinfo() error" << std::endl;
		return;
	}

	struct sockaddr_in *ip = reinterpret_cast<struct sockaddr_in *>(res->ai_addr);

	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_port = htons(port);
	this->serverAddress.sin_addr = ip->sin_addr;
	// this->serverAddress.sin_addr.s_addr = INADDR_ANY;
	freeaddrinfo(res);
}

void Server::start(Config &mainConf)
{
	unsigned short port;
	std::string hostName;
	std::set<int>::iterator portsIt;
	int opt = 1;
	int socketIndex = 0;

	for (int i = 0; i < mainConf.how_mn_servers(); i++)
	{
		for (portsIt = mainConf.srvConf[i].ports.begin(); portsIt != mainConf.srvConf[i].ports.end(); portsIt++)
		{
			port = *portsIt;
			hostName = mainConf.srvConf[i].name;

			// int opt = 1;
			this->serverSocketsFd.push_back(socket(AF_INET, SOCK_STREAM, 0));
			if (this->serverSocketsFd[socketIndex] < 0)
			{
				perror("socket() failed");
				exit(EXIT_FAILURE);
			}

			// setnonblocking
			setNonBlocking(this->serverSocketsFd[socketIndex]);

			if (this->serverSocketsFd[i] < 0)
			{
				logger.Log(ERROR, "Error creating server socket");
				throw std::runtime_error("Error creating server socket");
			}

			// this solves the error of binding by reusing address
			if (setsockopt(this->serverSocketsFd[socketIndex], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
			{
				logger.Log(ERROR, "Error of binding by reusing address");
				throw std::runtime_error("Error of binding by reusing address");
			}

			// set server address info
			setServerAddress(port, hostName);

			// bind socket
			if (bind(this->serverSocketsFd[socketIndex], (struct sockaddr *)&this->serverAddress, sizeof(this->serverAddress)) < 0)
			{
				// logger.Log(ERROR, "Error binding server socket");
				// throw std::runtime_error("Error binding server socket");
				std::cout << YELLOW_TEXT << "WARNING: An error occured and server cannot listen on " << port << " check the config file " << RESET_COLOR << std::endl;
				return;
			}

			// listen on
			if (listen(this->serverSocketsFd[socketIndex], CLIENTS_COUNT) < 0)
			{
				logger.Log(ERROR, "Error listening on socket");
				throw std::runtime_error("Error listening on socket port " + std::to_string(port));
			}

			// include serv conf to each socket
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
	bool closeConn;
	std::vector<struct pollfd> fds;
	ssize_t rc;
	struct pollfd tempPollFd;
	int currentPortInex;
	int endServer = false;
	int clientSd = -1;
	std::string http_resp;

	for (size_t i = 0; i < this->serverSocketsFd.size(); i++)
	{
		tempPollFd.fd = serverSocketsFd[i];
		tempPollFd.events = POLLIN;
		fds.push_back(tempPollFd);
		Socket sock;
		this->sockets.push_back(sock);
	}
	while (endServer == false)
	{
		closeConn = false;
		rc = poll(fds.data(), fds.size(), 3000);
		if (rc < 0)
		{
			std::cout << "poll() error\n";
			break;
		}
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (std::find(this->serverSocketsFd.begin(), this->serverSocketsFd.end(), fds[i].fd) != this->serverSocketsFd.end() && fds[i].revents != 0)
			{
				struct sockaddr_in client_addr;
				socklen_t client_addr_len = sizeof(client_addr);
				clientSd = accept(fds[i].fd, (struct sockaddr *)&client_addr, &client_addr_len);
				if (clientSd < 0)
				{
					std::cerr << "accept() failed\n";
					endServer = true;
					break;
				}
				tempPollFd.fd = clientSd;
				tempPollFd.events = POLLIN;
				fds.push_back(tempPollFd);
				currentPortInex = i;
				Socket sock;
				sockets.push_back(sock);
			}
			else if (fds[i].revents != 0)
			{
				// ------------------------------------------------------------------------------------------------------
				this->sockets.at(i).resetBuffer();
				if (this->sockets.at(i).allDataRead(fds.at(i).fd))
				{
					std::string joinedStr = this->sockets.at(i).getJoinedStr();
					http_resp = buildHttpResponse(currentPortInex, joinedStr, this->sockets.at(i).getBodySize());
					this->sockets.at(i).s_HttpResp = std::string(http_resp.c_str(), http_resp.length());
					this->sockets.at(i).setFull_lenght(http_resp.length());
					this->sockets.at(i).setInitiated(this->sockets.at(i).getCloseConnStat()); // set the data as readed !
				}
				// ------------------------------------------------------------------------------------------------------
			}
			if (this->sockets.at(i).getInitiated() == true)
			{
				do
				{
					rc = send(fds[i].fd, &this->sockets.at(i).s_HttpResp.c_str()[this->sockets.at(i).sent_offset], this->sockets.at(i).full_lenght, 0);
					this->sockets.at(i).sent_offset += (rc == -1 ? 0 : rc);
					this->sockets.at(i).s_HttpResp = &this->sockets.at(i).s_HttpResp.c_str()[this->sockets.at(i).sent_offset];
					std::cout << "sent_offset: " << this->sockets.at(i).sent_offset << "\n";
					std::cout << "full_lenght: " << this->sockets.at(i).full_lenght << "\n";
					std::cout << "------------------------------------------------------\n";
					if (this->sockets.at(i).sent_offset >= this->sockets.at(i).full_lenght)
						closeConn = true;
				} while (!closeConn);
			}
			if (closeConn)
			{
				close(fds[i].fd);
				fds[i].fd = -1;
				fds.erase(fds.begin() + i);
				this->sockets.at(i).eraseAll();
				this->sockets.erase(this->sockets.begin() + i);
			}
		}
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
