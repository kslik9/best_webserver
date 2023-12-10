#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"

class	HttpMessageChecker;
class	ServConf;
class	Config;
class	Socket;



class Server
{
	private:
		sockaddr_in								serverAddress;
		std::vector<int>						serverSocketsFd;
		std::multimap<std::string, std::string>	portsAndHosts;
		std::vector<ServConf>					conf;
		int										contentLen;
		int										bodySize;
		std::vector<Socket>						sockets;
	public:
		Server();
		~Server();
		bool reachedTheEnd(std::string bufferStr, int bytesReceived);
		void start(Config &mainConf);
		void waitClients();
		std::string buildHttpResponse(int socketIndex, std::string request);
		Server &operator=(Server const &rhs);
		void	setServerAddress(unsigned short &port, std::string &hostName);

};

#endif /* ********************************************************** SERVER_H */