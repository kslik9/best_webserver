#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "webserv.hpp"

struct serv_conf
{
	std::string host;
	int port;
	std::string errorPages;
	int clientBodyLimit;
	std::string root;
	std::string routes;
};
class Config
{

public:
	Config();
	Config(Config const &src);
	Config(std::string conf);
	~Config();
	Config &operator=(Config const &rhs);
	// 
	unsigned int getPort() const;
	serv_conf srvConf;
	void parseConf();
private:
	std::vector<std::string> raw_data;
	unsigned int port;
};

std::ostream &operator<<(std::ostream &o, Config const &i);

#endif /* ********************************************************** CONFIG_H */