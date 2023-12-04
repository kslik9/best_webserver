#ifndef CONFIG_HPP
#define CONFIG_HPP
#include "ServConf.hpp"
#include "webserv.hpp"
#include <set>
class ServConf;

typedef std::vector<std::string> vec;
typedef std::map<std::string, std::string> mp;

struct locate
{
	std::string autoindex;
	std::string cgi_path;
	std::string cgi_extension;
	std::string index;
	std::string root;
	std::string redirect;
	std::string method;
	std::string method1;
	std::string method2;
	std::string method3;
};

typedef std::map<std::string, mp > map_last;


class Config
{
	public:
		Config();
		Config(Config const &src);
		Config(std::string conf);
		void parsePort(int i);
		~Config();
		Config &operator=(Config const &rhs);
		// 
		int 	how_mn_servers();
		void filldata();
		void display_all(ServConf srvConf);
		int servers_number;
		void parse_error(int i);
		unsigned int getPort() const;
		void parseInfosStr(std::string name , int leng, std::string &host, int i);
		mp get_info_for_loca(std::string str);
		void parseInfosInt(std::string name , int leng, long long &host, int i);
		void parseLocation(int i);
		std::string value_fo_loca(vec::iterator it);
		void parseConf();
		std::vector<ServConf> srvConf; 
	private:
		static const int arr = 10;
		std::vector<std::string> raw_data;
		unsigned int port;
};

std::ostream &operator<<(std::ostream &o, Config const &i);

#endif /* ********************************************************** CONFIG_H */