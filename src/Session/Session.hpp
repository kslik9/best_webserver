#ifndef SESSION_HPP
#define SESSION_HPP

#include "webserv.hpp"

class Server;
class Config;

class Session
{

public:
	Session();
	Session(Session const &src);
	Session(Server &server, Config &config);
	~Session();

	Session &operator=(Session const &rhs);

private:
};

std::ostream &operator<<(std::ostream &o, Session const &i);

#endif /* ********************************************************* SESSION_H */