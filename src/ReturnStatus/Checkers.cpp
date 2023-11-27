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

std::string trim(std::string str) {
    unsigned int fIndex = 0;
    unsigned int lIndex = 0;
    unsigned int strLen = str.length();

    while (fIndex < strLen && str.at(fIndex) == ' ')
        fIndex++;

    lIndex = str.length() - 1;
    while (lIndex >= 0 && str.at(lIndex) == ' ')
        lIndex--;

    return str.substr(fIndex, lIndex - fIndex + 1);
}

bool isFile(std::string const &file) {
    return file.find(".") != std::string::npos ? true : false;
}

std::string getRouteStr(std::string &url) {
    int pos = 0;
    url = url.substr(1);
    std::string route = "/";
    // std::cout << url << std::endl;
    while ((pos = url.find("/")) != std::string::npos) {
        //here i will check if 
        std::string fragment = url.substr(0, pos);
        // std::cout << "fragment: " << fragment;
        if (isFile(fragment))
            return route;
        else
            route += (fragment + "/");
        url = url.substr(pos + 1);
    }
    if (!url.empty()) {
        // std::cout << "fragment: " << url;
        if (isFile(url))
            return route;
        else
            route += (url);
    }
    return route;
}

//check if there is any location match with the uri (target)
bool    HttpRequestChecker::checkLocationMatchRequestUri() {
    // std::map<std::string, locate > mp = config.srvConf.rout;
    // std::map<std::string, locate >::iterator it = mp.begin();
    // while (it != mp.end()) {
    //     std::string locationn = trim(it->first);
    // }
    std::string stringRoute = getRouteStr(target);
    std::cout << stringRoute << std::endl;
    return true;
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