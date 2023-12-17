#pragma once
#include "webserv.hpp"

#define BUFFER_SIZE 1024 * 1024
class Socket {
	private:
		long		contentLen;
		int			bodySize;
        std::string joinedStr;
        char        buffer[BUFFER_SIZE];
        bool        closeConnection;
		ssize_t		fullLength;
		ssize_t		sentOffset;
		bool		initiated;
	public:
		std::string	s_HttpResp;
		// 
		Socket();
		~Socket();
		void	    setContentLen(std::string bufferStr);
		void	    setBodySize(std::string bufferStr, int bytesReceived);
		int         getBodySize();
        void        resetBuffer();
        bool        allDataRead(int fd);
        std::string getJoinedStr() const;
        bool        getCloseConnStat();
		void		setSentOffset(ssize_t sentOffset);
		ssize_t		getSentOffset(void) const ;
		void		setInitiated(bool newdata);
		bool 		getInitiated(void) const;
		void		sets_HttpResp(std::string &newdata);
		std::string gets_HttpResp(void) const;
		void		eraseAll();
		long 		getContentLen2();
		void		setFullLength(ssize_t fullLenghtP);
		ssize_t		getFullLength();
		void		addToSentOffset(long num);
};
