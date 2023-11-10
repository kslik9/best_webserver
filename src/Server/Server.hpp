#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"

class Config;

class Server
{
private:
	Config &config;
	unsigned int SocketFd;
	unsigned int activeClients;
	sockaddr_in server_address;

public:
	Server(Config &config);
	Server(Server const &src);
	~Server();
	void start();
	void waitClients();
	unsigned int getSocketFd() const;
	Config getConfig() const;
	sockaddr_in getServer_address() const;
	Server &operator=(Server const &rhs);
};

#endif /* ********************************************************** SERVER_H */