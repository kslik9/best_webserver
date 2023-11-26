#include "HttpMessage.hpp"

bool    HttpMessage::checkNotAllowededChars() {
    std::string allowedChars  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	unsigned int	targetLen = target.length();

	for (int i = 1; i < targetLen; i++) {
		if (allowedChars.find(target[i]) == std::string::npos)
			return true;
	}
	return false;
}

bool    HttpMessage::checkUriLength() {
    if (target.length() > 2048)
		return true;
	return false;
}

bool    HttpMessage::checkRequestHttpMessage() {
    //check if the request body is larger than cliant max body size in config file
    return false;
}

bool    HttpMessage::checkLocationMatchRequestUri() {
    //check if there is any location match with the uri (target)
    return false;
}

bool    HttpMessage::checkLocationHasRedirection() {
    //check if the location have a redirection like return 301 /home/index.html
    return true;
}

bool    HttpMessage::checkMethodAllowed() {
    //check if the method is allowed or not in the location
    return true;
}

bool    HttpMessage::checkContentExistsInRoot() {
    //check if the content is exist in in root
    return true;
}

bool    HttpMessage::checkContentIsDir() {
    //check if the content is dir
    return true;
}

bool    HttpMessage::checkIndexFilesInDir() {
    //check if the directory has an index file
    return true;
}

bool    HttpMessage::checkAutoIndexOn() {
    //check if the index file is on
    return true;
}

bool    HttpMessage::checkLocationIncludesCgi() {
    //check if the location include cgi configurations
    return true;
}

bool    HttpMessage::checkDirIndedWithBackSlash() {
    
}