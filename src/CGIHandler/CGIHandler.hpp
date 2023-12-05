#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include "webserv.hpp"

typedef struct
{
    std::string path;
    std::ifstream *file_stream;
} php_script;

class CGIHandler
{

public:
	CGIHandler();
	CGIHandler(RequestData request);
	CGIHandler(CGIHandler const &src);
	~CGIHandler();
	CGIHandler &operator=(CGIHandler const &rhs);
	// 
	std::string process();
	void init_env(RequestData request);
	// 
private:
	std::map<std::string, std::string> keyValue;
	std::vector<const char *> env_vec;
};

#endif /* ****************************************************** CGIHANDLER_H */