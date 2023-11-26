#include "HttpRequestChecker.hpp"

bool    HttpRequestChecker::checkNotAllowededChars() {
    std::string allowedChars  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	unsigned int	targetLen = target.length();

	for (int i = 1; i < targetLen; i++) {
		if (allowedChars.find(target[i]) == std::string::npos)
			return true;
	}
	return false;
}

bool    HttpRequestChecker::checkUriLength() {
    if (target.length() > 2048)
		return true;
	return false;
}

bool    HttpRequestChecker::checkRequestHttpMessage() {
    //check if the request body is larger than cliant max body size in config file
    return false;
}

bool    HttpRequestChecker::checkLocationMatchRequestUri() {
    //check if there is any location match with the uri (target)
    return false;
}

bool    HttpRequestChecker::checkLocationHasRedirection() {
    //check if the location have a redirection like return 301 /home/index.html
    return true;
}

bool    HttpRequestChecker::checkMethodAllowed() {
    //check if the method is allowed or not in the location
    return true;
}

bool    HttpRequestChecker::checkContentExistsInRoot() {
    //check if the content is exist in in root
    return true;
}

bool    HttpRequestChecker::checkContentIsDir() {
    //check if the content is dir
    return true;
}

bool    HttpRequestChecker::checkIndexFilesInDir() {
    //check if the directory has an index file
    return true;
}

bool    HttpRequestChecker::checkAutoIndexOn() {
    //check if the index file is on
    return true;
}

bool    HttpRequestChecker::checkLocationIncludesCgi() {
    //check if the location include cgi configurations
    return true;
}

bool    HttpRequestChecker::checkDirIndedWithBackSlash() {
    return true;
}