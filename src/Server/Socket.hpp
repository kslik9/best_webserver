#pragma once
#include "webserv.hpp"

#define BUFFER_SIZE 1024 * 1024
class Socket {
	public:
		int			contentLen;
		int			bodySize;
        std::string joinedStr;
        char        buffer[BUFFER_SIZE];
        bool        closeConnection;
		std::string	s_HttpResp;
		ssize_t		full_lenght;
		ssize_t		sent_offset;
		bool		initiated;
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
		void		setSent_offset(ssize_t sent_offset);
		ssize_t		getSent_offset(void) const ;
		void		setFull_lenght(ssize_t newdata);
		ssize_t 	getFull_lenght(void) const;
		void		setInitiated(bool newdata);
		bool 		getInitiated(void) const;
		void		sets_HttpResp(std::string &newdata);
		std::string gets_HttpResp(void) const;
		void		eraseAll();
};
