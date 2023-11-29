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
std::string t_ry(std::string str, std::string &host, std::string name, int len, int flag)
{
	int i = 0;
	size_t k = 0;
	int mindex = 1;
	static int meth = 0;
	static std::string last = "none";
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
					return "none";
				}
				else if(mindex == meth && name  == "method")
					break;
				else
					mindex++;
            }
        }
        i++; 
    }
	if(host == last)
		host = "none";
	last = host;
	return host;
}
mp Config::get_info_for_loca(std::string str)
{
	mp tm;
	std::string tmp = "none";
	mp::iterator it;
	tm["autoindex"] = t_ry(str, tmp, "autoindex", 9, 1);
	tm["cgi_path"] = t_ry(str, tmp, "cgi_path", 9, 1);
	tm["cgi_extension"] = t_ry(str, tmp, "cgi_extension", 14, 1);
	tm["index"] = t_ry(str, tmp, "index", 5, 1);
	tm["root"] = t_ry(str, tmp, "root", 4, 1);
	tm["method1"] = t_ry(str, tmp, "method", 8, 1);
	tm["method2"] = t_ry(str, tmp, "method", 8, 1);
	tm["method3"] = t_ry(str, tmp, "method", 8, 1);
	tm["method4"] = t_ry(str, tmp, "method", 8, 1);
	tm["redirect"] = t_ry(str, tmp, "redirect", 9, 1);
	tm["redirect"] = t_ry(str, tmp, "redirect", 8, 0);

	return tm;
}
void Config::display_all(serv_conf srvConf)
{
	std::cout << "hey\n";
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
		mp::iterator oi;
			it = srvConf.rout.begin();
			while(it != srvConf.rout.end())
			{
				std::cout <<"route =>{" <<  it->first << "}:\n" ;
				oi = it->second.begin();
				while(oi != it->second.end())
				{
					std::cout << oi->first << " => " << oi->second << " ";
					*oi++;
				}
				*it++;
				std::cout << std::endl;
			}
		std::cout << "----------------------------------------------------------------------\n";
		i++;
	}
}
std::string get_name_good(std::string name)
{
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
	int c = 0;
	for(int i = 0;i < name.length() + 1 ;i++)
	{
		if(name[i] == '/')
			c++;
	}
	if(c > 1)
	{
		if(name[name.length() - 1] == '/')
			name[name.length() - 1] = ' ';
	}
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
	return name;
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
		tmp = get_name_good(pop->first);
		srvConf[0].rout[tmp] = get_info_for_loca(pop->second);
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
		display_all(srvConf[0]);
		exit(0);

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