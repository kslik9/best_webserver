#include "Config.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Config::Config()
{
	srvConf.resize(10);
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
int whichMethAmI(std::string str)
{
	int i = 0 ;
	size_t k = 0;
	int c = 0 ;
	while(i < str.length())
	{
		if(k < str.length() + 1)
			k = str.find("method", k + 1);
		else 
			break;
		if(k != std::string::npos)
			c++;
		i++;
	}
	return c;
}
void t_ry(std::string str, std::string &host, std::string name, int len, int flag)
{
	int i = 0;
	size_t k = 0;
	int mindex = 1;
	static int meth = 0;
	int howmuch_meth = whichMethAmI(str);
	if(flag == 0)
		meth = 0;
	if(name  == "method")
		meth++;
    while (i < str.length()) 
	{
        k = str.find(name, k);
        if (k != std::string::npos) 
		{
            size_t j = str.find(";", k); 
            if (j != std::string::npos) 
			{
                host = str.substr(k + len, j - (k + len));
				host.erase(std::remove_if(host.begin(), host.end(), ::isspace), host.end());
                k = j;
				if(meth > howmuch_meth)
				{
					host = "none";
					return;
				}
				else if(mindex == meth && name  == "method")
					break;
				else
					mindex++;
            }
        }
        i++; 
    }
}
locate Config::get_info_for_loca(std::string str)
{
	struct locate tm;
	t_ry(str, tm.autoindex, "autoindex", 9, 1);
	t_ry(str, tm.cgi_path, "cgi_path", 9, 1);
	t_ry(str, tm.cgi_extension, "cgi_extension", 14, 1);
	t_ry(str, tm.index, "index", 5, 1);
	t_ry(str, tm.root, "root", 4, 1);
	t_ry(str, tm.method, "method", 6, 1);
	t_ry(str, tm.method1, "method", 6, 1);
	t_ry(str, tm.method2, "method", 6, 1);
	t_ry(str, tm.method3, "method", 6, 1);
	t_ry(str, tm.redirect, "redirect", 9, 1);
	t_ry(str, tm.redirect, "redirect", 9, 0);

	return tm;
}
void Config::display_all(serv_conf srvConf)
{
	int i = 0;
	while(i < this->servers_number)
	{
		std::cout << "server number {" << i << "}\n";
		std::cout << "the host is " << srvConf.host << std::endl;
		std::cout << "the port is " << srvConf.port << std::endl;
		std::cout << "the error page is " << srvConf.errorPages << std::endl;
		std::cout << "the name is " << srvConf.name << std::endl;
		std::cout << "the body max size is " << srvConf.clientBodyLimit << std::endl;
		map_last::iterator it;
		std::cout << "-------routes----------\n";
			it = srvConf.rout.begin();
			while(it != srvConf.rout.end())
			{
				std::cout << "route name = is " << it->first ;
				std::cout << " auto index =>" << it->second.autoindex ;
				std::cout << " cgi path =>" << it->second.cgi_path ;
				std::cout << " cgi extension =>" << it->second.cgi_extension ;
				std::cout << " index =>" << it->second.index ;
				std::cout << " root =>" << it->second.root ;
				if(it->second.redirect[0])
					std::cout << " redirect =>" << it->second.redirect ;
				std::cout << " first method =>" << it->second.method ;
				std::cout << " second method =>" << it->second.method1 ;
				std::cout << " third method =>" << it->second.method2 ;
				std::cout << " forth method =>" << it->second.method3 ;
				*it++;
				std::cout << std::endl;
			}
		std::cout << "----------------------------------------------------------------------\n";
		i++;
	}
}
void Config::parseLocation(int i)
{
	std::string tmp;
	std::string value;
	vec::iterator it = this->raw_data.begin();
	while(it != this->raw_data.end())
	{
		tmp = *it;
		size_t loc = tmp.find("location");
		if(loc != std::string::npos)
		{
			size_t pos = tmp.find('/');
			tmp = tmp.substr(pos - 1);

			value = value_fo_loca(it);
			srvConf[0].routes[tmp] = value;
		}
		it++;
	}
	mp::iterator pop;
	map_last::iterator iter = srvConf[0].rout.begin();
	pop = srvConf[0].routes.begin();
	while(pop != srvConf[0].routes.end())
	{		
		srvConf[0].rout[pop->first] = get_info_for_loca(pop->second);
		pop++;
	}	
}
void Config::parseInfosStr(std::string name , int leng, std::string &host)
{
	vec::iterator it = this->raw_data.begin();
	std::string tmp;
	while(it != this->raw_data.end())
	{
		tmp = *it;
		size_t loc = tmp.find(name);
		if(loc != std::string::npos)
		{
			tmp = tmp.substr(loc + leng );
			host = tmp;
			break;
		}
		it++;
	}
	std::replace(host.begin(), host.end(), ';', ' ');
	host.erase(std::remove_if(host.begin(), host.end(), ::isspace), host.end());


}
void Config::parseInfosInt(std::string name , int leng, long long &host)
{
	vec::iterator it = this->raw_data.begin();
	std::string tmp;
	while(it != this->raw_data.end())
	{
		tmp = *it;
		size_t loc = tmp.find(name);
		if(loc != std::string::npos)
		{
			tmp = tmp.substr(loc + leng );
			host = std::atof(tmp.c_str());
			break;
		}
		it++;
	}
}
int 	Config::how_mn_servers()
{
	int i = 0 ;
	size_t k = 0;
	vec::iterator it = this->raw_data.begin();
	std::string tmp;
	int c = 0 ;
	while(it != this->raw_data.end())
	{
		tmp = *it;
		tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
		if(tmp == "server")
			c++;

		it++;
	}
	return c;
}
void Config::parseConf()
{
	this->servers_number = how_mn_servers();
	int i = 0;
	while(i < this->servers_number)
	{
		parseLocation(i);
		parseInfosStr("host", 4, srvConf[i].host);
		parseInfosStr("error", 5, srvConf[i].errorPages);
		parseInfosStr("name", 4, srvConf[i].name);
		parseInfosInt("listen", 6, srvConf[i].port);
		parseInfosInt("body_size", 10, srvConf[i].clientBodyLimit);
		i++;
	}

}
Config::Config(std::string conf)
{
	srvConf.resize(10);
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
		// display_all(srvConf[0]);
		// exit(0);

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