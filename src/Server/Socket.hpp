#pragma once
#include "webserv.hpp"

#define BUFFER_SIZE 1024 * 1024
class Socket {
	private:
		int			contentLen;
		int			bodySize;
		int         socketFd;
        std::string joinedStr;
        char        buffer[BUFFER_SIZE];
        bool        closeConnection;
	public:
		Socket();
		void	    setContentLen(std::string bufferStr);
		void	    setBodySize(std::string bufferStr, int bytesReceived);
		int         getBodySize();
        void        resetBuffer();
        bool        allDataRead(int fd);
        std::string getJoinedStr() const;
        bool        getCloseConnStat();
};