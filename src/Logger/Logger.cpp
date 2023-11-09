
#include "Logger.hpp"

Logger::Logger() : logFileName("webserv.log")
{
	char timeStr[11];
	std::time_t currentTime = std::time(nullptr);
	struct std::tm *localTime = std::localtime(&currentTime);
	std::strftime(timeStr, sizeof(timeStr), "%d-%m-%Y", localTime);
	logFile.open("./logs/[" + static_cast<std::string>(timeStr) + "]" + logFileName, std::ios::app);
	if (!logFile.is_open())
		throw std::runtime_error("Error: Could not open the log file.");
}

Logger::Logger(const std::string &logFileName) : logFileName(logFileName)
{
	char timeStr[11];
	std::time_t currentTime = std::time(nullptr);
	struct std::tm *localTime = std::localtime(&currentTime);
	std::strftime(timeStr, sizeof(timeStr), "%d-%m-%Y", localTime);
	logFile.open("./logs/[" + static_cast<std::string>(timeStr) + "]" + logFileName, std::ios::app);
	if (!logFile.is_open())
		throw std::runtime_error("Error: Could not open the log file.");
}

Logger::~Logger()
{
	if (logFile.is_open())
	{
		logFile.close();
	}
}

void Logger::Log(LogLevel level, const std::string &message)
{
	if (logFile.is_open())
	{
		time_t currentTime = time(nullptr);
		struct tm *localTime = localtime(&currentTime);
		char timeStr[100];
		strftime(timeStr, sizeof(timeStr), "[%Y-%m-%d %H:%M:%S] ", localTime);

		std::string logLevelStr;
		switch (level)
		{
		case ERROR:
			logLevelStr = "[ERROR] ";
			break;
		case WARNING:
			logLevelStr = "[WARNING] ";
			break;
		case INFO:
			logLevelStr = "[INFO] ";
			break;
		}
		logFile << timeStr << logLevelStr << message << std::endl;
		std::cout << timeStr << logLevelStr << message << std::endl;
		logFile.flush();
	}
	else
	{
		std::cerr << "Error: Log file is not open." << std::endl;
	}
}

Logger::Logger(const Logger& copy)
{
	*this = copy;
}

Logger &Logger::operator=(Logger const &copy)
{
	// this->logFile = copy.logFile;
	this->logFileName = copy.logFileName;
	return (*this);
}
