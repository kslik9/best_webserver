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

#include <list>
#include <set>

// /hello/images
std::list<std::string>  extractRoutes(std::string stringRoute) {
    std::list<std::string> routes;

    //  std::cout << stringRoute << std::endl;
    routes.push_back(stringRoute);
    int stringRouteLen = stringRoute.length();
    int pos;
    while ((pos = stringRoute.find_last_of("/")) != std::string::npos) {
        
        std::string su = stringRoute.substr(0, pos);
        if (su.empty())
        {
            routes.push_back("/");
            break;
        }
        routes.push_back(su);
        stringRoute = su;
    }
    return routes;
}

//check if there is any location match with the uri (target)
bool    HttpRequestChecker::checkLocationMatchRequestUri() {
    std::map<std::string, std::string> abstractLocation;
    abstractLocation.insert(std::make_pair("autoindex", "on"));
    abstractLocation.insert(std::make_pair("index", "index.html"));
    abstractLocation.insert(std::make_pair("method", "GET"));
    abstractLocation.insert(std::make_pair("redirect", "https://www.youtube.com/watch?v=Zgz8ybG6l-U"));


    std::set<std::string> abstractLocationsFromConfig;
    std::list<std::string> extractedRoutes;
    std::string stringRoute;

    // test.insert("/");
    // abstractLocationsFromConfig.insert("/");
    abstractLocationsFromConfig.insert("/data");
    abstractLocationsFromConfig.insert("/data/hello");
    abstractLocationsFromConfig.insert("/images");

    stringRoute = getRouteStr(target);
    extractedRoutes = extractRoutes(stringRoute);


    //iterate until finding a match location
    for (std::list<std::string>::iterator it = extractedRoutes.begin(); it != extractedRoutes.end(); ++it) {
        for (std::set<std::string>::iterator itt = abstractLocationsFromConfig.begin(); itt != abstractLocationsFromConfig.end(); ++itt) {
            if (*it == *itt)
            {
                //in this step if a route match, it will store the location <map>
                std::cout << "wakayna al7bs: " << *it << std::endl;
                this->location = abstractLocation;
                return true;
            }
        }
    }
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
