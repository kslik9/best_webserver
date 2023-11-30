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

// void parse_request(const std::string &request, std::string &method, std::string &target) {
// 	try
// 	{
// 		std::istringstream iss(request);
// 		iss >> method >> target;
// 	}
// 	catch (const std::exception &e)
// 	{
// 		std::cerr << e.what() << '\n';
// 		method = "GET";
// 		target = "/";
// 	}
// }

void Server::start() {
	for (int i = 0; i < config.servers_number; i++) {
		int opt = 1;
		this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
		if (socketFd < 0)
		{
			perror("socket() failed");
			exit(EXIT_FAILURE);
		}
		//setnonblocking
		setNonBlocking(this->socketFd);
		

		if (this->socketFd < 0)
		{
			logger.Log(ERROR, "Error creating server socket");
			throw std::runtime_error("Error creating server socket");
		}
		// this solves the error of binding by reusing address
		if (setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		{
			logger.Log(ERROR, "Error of binding by reusing address");
			throw std::runtime_error("Error of binding by reusing address");
		}
		// binding socket with address 0.0.0.0:8080
		this->server_address.sin_family = AF_INET;
		this->server_address.sin_port = htons(config.srvConf[i].port);
		this->server_address.sin_addr.s_addr = INADDR_ANY;
		if (bind(this->socketFd, (struct sockaddr *)&this->server_address, sizeof(this->server_address)) < 0)
		{
			logger.Log(ERROR, "Error binding server socket");
			throw std::runtime_error("Error binding server socket");
		}
		// listen on 0.0.0.0:8080
		if (listen(this->socketFd, CLIENTS_COUNT) < 0)
		{
			logger.Log(ERROR, "Error listening on socket");
			throw std::runtime_error("Error listening on socket");
		}
		// -----------------------------------------------------
		std::cout << "Server is listening on "
				<< "http://0.0.0.0"
				<< ":" << this->config.getPort() << std::endl;
	}
}


void Server::waitClients()
{
	//return status
	// ReturnStatus rs;

	// std::map<std::string, locate>::iterator it = config.srvConf.rout.begin();
	// std::cout << it->first << std::endl;
	// std::cout << it->second.autoindex << std::endl;

	
	struct pollfd fds[CLIENTS_COUNT + 1];
	fds[0].fd = this->socketFd;
	fds[0].events = POLLIN | POLLPRI;
	this->activeClients = 0;
	// -----------------------------------------------------
	// fill all fds with 0
	for (int i = 1; i < CLIENTS_COUNT; i++)
		fds[i].fd = 0;
	// -----------------------------------------------------
	while (true)
	{
		int activity = poll(fds, CLIENTS_COUNT, 0);
		if (activity < -1)
			std::cout << "Error : L:36" << std::endl;
		else
		{
			// check if a client tryin to connect and add it to pollfd list
			if (fds[0].revents & POLLIN)
			{
				struct sockaddr_in client_addr;
				socklen_t client_addr_len = sizeof(client_addr);
				int clientSocket = accept(this->socketFd, (struct sockaddr *)&client_addr, &client_addr_len);
				
				//set the client socket as non blocking
				setNonBlocking(clientSocket);
				for (int i = 1; i < CLIENTS_COUNT; i++)
				{
					if (fds[i].fd == 0)
					{
						fds[i].fd = clientSocket;
						fds[i].events = POLLIN | POLLPRI;
						this->activeClients++;
						std::cout << "new connection!! socket fd is " << clientSocket << " - " << inet_ntoa(client_addr.sin_addr) << std::endl;
						break;
					}
				}
			}
			
			// check data from clients
			for (int i = 1; i < CLIENTS_COUNT; i++) {
				if (fds[i].fd > 0 && (fds[i].revents & POLLIN)) {
					char *buffer = new char[BUFFER_SIZE];
					ssize_t bytes_received = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
					if (bytes_received < 0 || bytes_received == 0)
					{
						std::cout << "fd " << fds[i].fd << " removed\n";
						close(fds[i].fd);
						fds[i].fd = 0;
						fds[i].events = 0;
						fds[i].revents = 0;
						this->activeClients--;
					}
					else
					{
						std::string str_buffer(buffer);
						std::string http_resp = buildHttpResponse(str_buffer);
						send(fds[i].fd, http_resp.c_str(), http_resp.length(), 0);
						close(fds[i].fd);
					}
					delete[] buffer;
				}
				
			}
		}
	}

	close(this->socketFd);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

unsigned int Server::getSocketFd() const
{
	return this->socketFd;
}

Config Server::getConfig() const
{
	return this->config;
}

sockaddr_in Server::getServer_address() const
{
	return this->server_address;
}

/* ************************************************************************** */