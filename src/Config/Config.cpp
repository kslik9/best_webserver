#include "Config.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Config::Config()
{
	srvConf.resize(10);
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
	size_t i = 0 ;
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
	size_t i = 0;
	size_t k = 0;
	int mindex = 1;
	static int meth = 0;
	host = "";
	static std::string last = "";
	size_t j;
	int howmuch_meth = whichMethAmI(str);
	if(flag == 0)
		meth = 0;
	if(name  == "method")
		meth++;
    while (i < str.length()) 
	{
		if(k < str.length())
		{
			k = str.find(name, k);
		}
        if (k != std::string::npos) 
		{
			if(k < str.length())
            	j = str.find(";", k); 
            if (j != std::string::npos) 
			{
                host = str.substr(k + len, j - (k + len));
				host.erase(std::remove_if(host.begin(), host.end(), ::isspace), host.end());
                k = j;
				if(meth > howmuch_meth)
				{
					host = "";
					return "";
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
		host  = "";
	else
		last = host;
	return host;
}
mp Config::get_info_for_loca(std::string str)
{
	mp tm;
	std::string tmp = "";
	mp::iterator it;
	tm["autoindex"] = t_ry(str, tmp, "autoindex", 9, 1);
	tm["cgi_path"] = t_ry(str, tmp, "cgi_path", 9, 1);
	tm["cgi_extension"] = t_ry(str, tmp, "cgi_extension", 14, 1);
	tm["index"] = t_ry(str, tmp, "index", 5, 1);
	tm["root"] = t_ry(str, tmp, "root", 4, 1);
	tm["method1"] = t_ry(str, tmp, "method", 7, 1);
	tm["method2"] = t_ry(str, tmp, "method", 7, 1);
	tm["method3"] = t_ry(str, tmp, "method", 7, 1);
	tm["method4"] = t_ry(str, tmp, "method", 7, 1);
	tm["redirect"] = t_ry(str, tmp, "redirect", 9, 1);
	tm["redirect"] = t_ry(str, tmp, "redirect", 8, 0);
	tm["upload_directory"] = t_ry(str, tmp, "upload_directory", 17, 1);
	tm["body_max_size"] = t_ry(str, tmp, "body_max_size", 14, 1);

	return tm;
}
void Config::display_all(ServConf srvConf)
{
	
		std::cout << "the host is " << srvConf.host << std::endl;
		std::cout << "the ports is ";
		std::set<int>::iterator po = srvConf.ports.begin();
		while(po != srvConf.ports.end())
		{
			std::cout << *po << " ";
			++po;
		}
		std::cout << std::endl;
		std::cout << "the error pages is [";
		mp::iterator p = srvConf.errorPages.begin();
		while(p != srvConf.errorPages.end())
		{
			std::cout << "code error =>[" << p->first << "]path=>[" << p->second << "]|";
			*p++;
		}
		std::cout << "]" <<std::endl;
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
}
std::string get_name_good(std::string name)
{
	name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
	int c = 0;
	for(size_t i = 0; i < name.length() + 1 ; i++)
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
	vec::iterator it = this->srvConf[i].my_data.begin();
	while(it != this->srvConf[i].my_data.end())
	{
		tmp = *it;
		size_t loc = tmp.find("location");
		if(loc != std::string::npos)
		{
			size_t pos = tmp.find('/');
			tmp = tmp.substr(pos - 1);

			value = value_fo_loca(it);
			srvConf[i].routes[tmp] = value;
		}
		it++;
	}
	mp::iterator pop;
	pop = srvConf[i].routes.begin();
	while(pop != srvConf[i].routes.end())
	{
		tmp = get_name_good(pop->first);
		srvConf[i].rout[tmp] = get_info_for_loca(pop->second);
		pop++;
	}	
}
void Config::parseInfosStr(std::string name , int leng, std::string &host, int j)
{
	vec::iterator it = this->srvConf[j].my_data.begin();
	std::string tmp;
	while(it != this->srvConf[j].my_data.end())
	{
		tmp = *it;
		// std::cout << *it << std::endl;
		size_t loc = tmp.find(name);
		if(loc != std::string::npos)
		{
				tmp = tmp.substr(loc + leng );
				host = tmp;
				break;
		}
		// std::cout << i << std::endl;
		it++;
	}
	std::replace(host.begin(), host.end(), ';', ' ');
	host.erase(std::remove_if(host.begin(), host.end(), ::isspace), host.end());
}
void Config::parseInfosInt(std::string name , int leng, long long &host, int i)
{
	vec::iterator it = this->srvConf[i].my_data.begin();
	std::string tmp;
	while(it != this->srvConf[i].my_data.end())
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
void Config::filldata()
{
	int i = 0;
	int j = 0;
	std::string tmp;
	vec::iterator it = this->raw_data.begin();
	while(it != this->raw_data.end())
	{
		tmp = *it;
		if(tmp == "server")
			j++;
		i = j - 1;
		this->srvConf[i].my_data.push_back(tmp);
		it++;
	}
}
void Config::parse_error(int i)
{
	vec::iterator it = this->srvConf[i].my_data.begin();
	std::string tmp;
	std::string tmp2;

	std::string str;
	while(it != this->srvConf[i].my_data.end())
	{
		size_t k = 0;
		str = *it;
		str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
		k = str.find("error", k);
		if(k != std::string::npos)
		{
			if(k + 8 > str.length())
				break;
			tmp = str.substr(k + 5, 3);
			tmp2 = str.substr(k + 8);
			if(tmp2[tmp2.length() - 1] == ';')
				tmp2[tmp2.length() - 1] = ' ';
			tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
			tmp2.erase(std::remove_if(tmp2.begin(), tmp2.end(), ::isspace), tmp2.end());
			this->srvConf[i].errorPages[tmp] = tmp2;
		}
		*it++;
	}
}
void reframe(std::string &port)
{
	if(port[port.length() - 1] == ';')
		port[port.length() - 1] = ' ';
	port.erase(std::remove_if(port.begin(), port.end(), ::isspace), port.end());
}
void Config::parsePort(int i)
{
	vec::iterator it = this->srvConf[i].my_data.begin();
	std::string tmp;
	int p;
	size_t k;
	std::string port;
	while(it != this->srvConf[i].my_data.end())
	{
		tmp = *it;
		k = tmp.find("port");
		if(k != std::string::npos)
		{
			port = tmp.substr(k +4);
			reframe(port);
			p = std::atof(port.c_str());
			this->srvConf[i].ports.insert(p);
		}
		it++;
	}
}
void Config::parseConf()
{
	this->servers_number = how_mn_servers();
	int i = 0;
	filldata();
	while(i < this->servers_number)
	{
		parseLocation(i);
		parse_error(i);
		parseInfosStr("host", 4, srvConf[i].host, i);
		parseInfosStr("name", 4, srvConf[i].name, i);
		parsePort(i);
		parseInfosInt("body_size", 10, srvConf[i].clientBodyLimit, i);
		i++;
	}
}
Config::Config(std::string conf)
{
	srvConf.resize(10);
	this->port = 8080;
	int i = 0;
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
		while(i < this->servers_number)
		{
			// display_all(srvConf[i]);
			i++;
		}

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
	this->port = rhs.port;
	this->raw_data = rhs.raw_data;
	return *this;
}

std::ostream &operator<<(std::ostream &o, Config const &i)
{
	(void)i;
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

