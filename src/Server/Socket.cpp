#include "Socket.hpp"

Socket::Socket() {

}

Socket::Socket(short portIndx) {
    this->contentLen = -2;
    this->bodySize = 0;
    this->closeConnection = false;
    this->portIndex = portIndx;
}

Socket::~Socket() {
    
}

int countContentLen(std::string bufferStr) {
	std::string target = "Content-Length: ";

    size_t found = bufferStr.find(target);

    if (found != std::string::npos) {
        found += target.length();
        size_t end = bufferStr.find("\r\n", found);
        std::string lengthStr = bufferStr.substr(found, end - found);

        // Convert string to integer
		// std::cout << "len::: " << lengthStr << "\n";
        int contentLength = std::stoi(lengthStr);
        return contentLength;
    }
	return -1;
}

int countBodySize(std::string bufferStr, int bytesReceived) {
	if (bytesReceived < 0)
		return 0;
	int foundbrbn = bufferStr.find("\r\n\r\n");

	// std::cout << "shoko: " << bufferStr << std::endl;
	if (bufferStr.find("\r\n\r\n") != std::string::npos) {
		// std::cout << "ki: [[" << bufferStr.substr(foundbrbn + 4) << "]\n";
		std::cout << "found\n";
		return bytesReceived - (foundbrbn + 4);
	}
	return bytesReceived;
}


void    Socket::setContentLen(std::string bufferStr) {
    if (this->contentLen == -2)
        this->contentLen = countContentLen(bufferStr);
}

void    Socket::setBodySize(std::string bufferStr, int bytesReceived) {
    this->bodySize += countBodySize(bufferStr, bytesReceived);
}

int Socket::getBodySize() {
    return bodySize;
}

void    Socket::resetBuffer() {
    memset(this->buffer, '\0', BUFFER_SIZE);
}

bool    Socket::allDataRead(int fd) {
    int bytesReceived;
    bytesReceived = recv(fd, buffer, BUFFER_SIZE, 0);
    std::string bufferStr(buffer, bytesReceived);
    setContentLen(bufferStr);
    setBodySize(bufferStr, bytesReceived);
    std::cout << "bytes received : " << bytesReceived << std::endl;
    std::cout << "con_len        : " << this->contentLen << std::endl;
    std::cout << "body_size      : " << this->bodySize << std::endl;
    if (bytesReceived < 0) {
		if (this->bodySize >= this->contentLen) {
            joinedStr.append(bufferStr);
		    this->closeConnection = true;
            return true;
        }
	}
    if (bytesReceived == 0) {
		joinedStr.append(bufferStr);
		this->closeConnection = true;
		return true;
	}
    if (this->bodySize >= this->contentLen) {
        closeConnection = true;
        joinedStr.append(bufferStr);
        return true;
	}
    joinedStr.append(bufferStr);
    return false;
}

std::string Socket::getJoinedStr() const {
    return this->joinedStr;
}

bool        Socket::getCloseConnStat() {
    return this->closeConnection;
}

void    Socket::setPortIndex(short i) {
    this->portIndex = i;
}

short    Socket::getPortIndex() const {
    return this->portIndex;
}

int Socket::getContentLen() const {
    return this->contentLen;
}