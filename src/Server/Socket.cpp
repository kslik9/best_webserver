#include "Socket.hpp"

Socket::Socket() {
    this->contentLen = -2;
    this->bodySize = 0;
    this->closeConnection = false;
    
    this->sentOffset = 0;
    this->fullLength = 0;
    this->initiated = false;
}

Socket::~Socket() {
    
}

int getContentLen(std::string bufferStr) {
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
		return bytesReceived - (foundbrbn + 4);
	}
	return bytesReceived;
}



void    Socket::setContentLen(std::string bufferStr) {
    if (this->contentLen == -2)
        this->contentLen = getContentLen(bufferStr);
}

long    Socket::getContentLen2() {
    return this->contentLen;
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

    std::string bufferStr(buffer, (bytesReceived < 0 ? 0 : bytesReceived));
    setContentLen(bufferStr);
    setBodySize(bufferStr, bytesReceived);
    if (bytesReceived < 0) {
		if (this->bodySize >= this->contentLen) {
            joinedStr.append(bufferStr);
		    this->closeConnection = true;
            return true;
        }
	}
    if (bytesReceived == 0) {
		// joinedStr.append(bufferStr);
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




void Socket::setInitiated(bool newdata)
{
    this->initiated = newdata;
}

bool Socket::getInitiated(void) const
{
    return this->initiated;
}

void Socket::sets_HttpResp(std::string &newdata)
{
    ssize_t len = newdata.length();
    this->s_HttpResp = std::string(newdata.c_str(), len);
}

std::string Socket::gets_HttpResp(void) const
{
    return this->s_HttpResp;
}

void Socket::eraseAll()
{
    this->s_HttpResp.clear();
    this->fullLength = 0;
    this->sentOffset = 0;
    this->initiated = false;
}


void    Socket::setFullLength(ssize_t fullLengthP) {
    this->fullLength = fullLengthP;
}

ssize_t Socket::getFullLength() {
    return this->fullLength;
}

void    Socket::addToSentOffset(long num) {
    this->sentOffset += num;
}

void Socket::setSentOffset(ssize_t newdata)
{
    this->sentOffset = newdata;
}

ssize_t Socket::getSentOffset(void) const
{
    return this->sentOffset;
}
