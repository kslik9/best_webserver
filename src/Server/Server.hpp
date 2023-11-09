#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>

class Server
{
	int SocketFd;
public:
	Server();
	Server(Server const &src);
	~Server();

	Server &operator=(Server const &rhs);

private:
};

#endif /* ********************************************************** SERVER_H */