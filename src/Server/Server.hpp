#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"
// #include "../ReturnStatus/ReturnStatus.hpp"

class Config;
class HttpMessage;

class Server
{
	private:
		Config &config;
		HttpMessage &httpMessage;
		int socketFd;
		unsigned int activeClients;
		sockaddr_in server_address;
	public:
		Server(Config &config, HttpMessage &httpMsg);
		Server(Server const &src, HttpMessage &httpMsg);
		~Server();
		void start();
		void waitClients();
		unsigned int getSocketFd() const;
		Config getConfig() const;
		sockaddr_in getServer_address() const;
		std::string buildHttpResponse(std::string request);
		Server &operator=(Server const &rhs);
};

#endif /* ********************************************************** SERVER_H */