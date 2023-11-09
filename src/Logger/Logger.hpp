#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "webserv.hpp"

class Logger
{
public:
	Logger();
	Logger(const std::string &logFileName);
	Logger(const Logger& copy);
	Logger &operator=(Logger const &copy);
	~Logger();
	void Log(LogLevel level, const std::string &message);

private:
	std::string logFileName;
	std::ofstream logFile;
};

extern Logger logger;

#endif