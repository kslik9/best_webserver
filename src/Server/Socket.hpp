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
		short		portIndex;
	public:
		Socket();
		Socket(short portIndx);
		~Socket();
		void	    setContentLen(std::string bufferStr);
		void	    setBodySize(std::string bufferStr, int bytesReceived);
        bool        allDataRead(int fd);
		void		setPortIndex(short i);
        std::string getJoinedStr() const;
        bool        getCloseConnStat();
		short		getPortIndex() const;
		int         getBodySize();
		int			getContentLen() const;
        void        resetBuffer();
};