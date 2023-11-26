#include "HttpMessageChecker.hpp"

bool    HttpMessageChecker::checkNotAllowededChars() {
    std::string allowedChars  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	unsigned int	targetLen = target.length();

	for (int i = 1; i < targetLen; i++) {
		if (allowedChars.find(target[i]) == std::string::npos)
			return true;
	}
	return false;
}

bool    HttpMessageChecker::checkUriLength() {
    if (target.length() > 2048)
		return true;
	return false;
}

bool    HttpMessageChecker::checkRequestHttpMessage() {
    //check if the request body is larger than cliant max body size in config file
    return false;
}

bool    HttpMessageChecker::checkLocationMatchRequestUri() {
    //check if there is any location match with the uri (target)
    return false;
}

bool    HttpMessageChecker::checkLocationHasRedirection() {
    //check if the location have a redirection like return 301 /home/index.html
    return true;
}

bool    HttpMessageChecker::checkMethodAllowed() {
    //check if the method is allowed or not in the location
    return true;
}

bool    HttpMessageChecker::checkContentExistsInRoot() {
    //check if the content is exist in in root
    return true;
}

bool    HttpMessageChecker::checkContentIsDir() {
    //check if the content is dir
    return true;
}

bool    HttpMessageChecker::checkIndexFilesInDir() {
    //check if the directory has an index file
    return true;
}

bool    HttpMessageChecker::checkAutoIndexOn() {
    //check if the index file is on
    return true;
}

bool    HttpMessageChecker::checkLocationIncludesCgi() {
    //check if the location include cgi configurations
    return true;
}

bool    HttpMessageChecker::checkDirIndedWithBackSlash() {
    return true;
}