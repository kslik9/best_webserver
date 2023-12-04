#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"
// #include "../ReturnStatus/ReturnStatus.hpp"

class Config;
class HttpMessageChecker;

// #include <multimap>
class Server
{
	private:
		Config								&config;
		sockaddr_in							serverAddress;
		std::vector<int>					serverSocketsFd;
		std::multimap<std::string, std::string>	portsAndHosts;
	public:
		Server(Config &config);
		Server(Server const &src);
		~Server();
		void start();
		void waitClients();
		Config getConfig() const;
		sockaddr_in getServer_address() const;
		std::string buildHttpResponse(std::string request);
		Server &operator=(Server const &rhs);
		void	setServerAddress(unsigned short &port, std::string &hostName);
};

#endif /* ********************************************************** SERVER_H */