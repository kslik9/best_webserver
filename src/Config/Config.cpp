#include "Config.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Config::Config()
{
}

Config::Config(const Config &src)
{
}
void Config::parseConf()
{
	// std::vector<std::string>::iterator it = this->raw_data.begin();
	// while(it != this->raw_data.end())
	// {
	// 	std::cout << *it << std::endl;
	// 	it++;
	// }

}
Config::Config(std::string conf)
{
	this->port = 8080;
	std::fstream file(conf);
	if (!file.is_open())
	{
		logger.Log(ERROR, "config file can't be open");
		throw std::runtime_error("config file can't be open");
	}
	else
	{
		std::string line;
		while (std::getline(file, line))
			this->raw_data.push_back(line);
		parseConf();
	}
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Config::~Config()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Config &Config::operator=(Config const &rhs)
{
	// if ( this != &rhs )
	//{
	// this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Config const &i)
{
	// o << "Value = " << i.getValue();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

unsigned int Config::getPort() const
{
	return this->port;
}

/* ************************************************************************** */