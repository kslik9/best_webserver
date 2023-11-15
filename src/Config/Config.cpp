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
int didWeFinish(std::string tmp)
{
	for(size_t i = 0; i < tmp.length(); i++)
	{
		if(tmp[i] == ']')
			return 1;
		else if(tmp[i] != ' ')
			return 2;
	}
	return 0;
}
std::string Config::value_fo_loca(vec::iterator it)
{
	*it++;
	*it++;
	std::string map;
	std::string tmp;
	tmp = *it;
	while(didWeFinish(tmp) != 1)
	{
		map = map + tmp;
		++it;
		tmp = *it;
	}
	return map;
}
void Config::parseConf()
{
	vec::iterator it = this->raw_data.begin();
	std::string tmp;
	std::string value;
	while(it != this->raw_data.end())
	{
		tmp = *it;
		size_t loc = tmp.find("location");
		if(loc != std::string::npos)
		{
			size_t pos = tmp.find('/');
			tmp = tmp.substr(pos - 1);

			value = value_fo_loca(it);
			srvConf.routes[tmp] = value;
		}
		it++;
	}
	mp::iterator pop;
	pop = srvConf.routes.begin();
	while(pop != srvConf.routes.end())
	{
		std::cout << pop->first << " " << pop->second << std::endl;
		pop++;
	}

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
	exit(0);
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