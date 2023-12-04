#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"

class	HttpMessageChecker;
class	ServConf;
class	Config;

class Server
{
	private:
		sockaddr_in								serverAddress;
		std::vector<int>						serverSocketsFd;
		std::multimap<std::string, std::string>	portsAndHosts;
		std::vector<ServConf>					conf;
	public:
		Server();
		~Server();
		void start(Config &mainConf);
		void waitClients();
		sockaddr_in getServer_address() const;
		std::string buildHttpResponse(int socketIndex, std::string request);
		Server &operator=(Server const &rhs);
		void	setServerAddress(unsigned short &port, std::string &hostName);
};

#endif /* ********************************************************** SERVER_H */