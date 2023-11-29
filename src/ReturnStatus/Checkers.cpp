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

std::string getRouteStr(std::string url) {
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

    std::string confLocation;
    std::list<std::string> extractedRoutes;
    std::string stringRoute;

    stringRoute = getRouteStr(target);
    extractedRoutes = extractRoutes(stringRoute);

    //iterate until finding a match location
    for (std::list<std::string>::iterator extractedRoutesIt = extractedRoutes.begin(); extractedRoutesIt != extractedRoutes.end(); ++extractedRoutesIt) {
        for (std::map<std::string, mp>::iterator locationsIt = config.srvConf[0].rout.begin(); locationsIt != config.srvConf[0].rout.end(); ++locationsIt) {
            confLocation = trim(locationsIt->first);
            if (*extractedRoutesIt == confLocation)
            {
                //in this step if a route match, it will store the location <map>
                // // std::cout << "wakayna al7bs: " << *extractedRoutesIt << "{-}" << confLocation << std::endl;
                this->location = locationsIt->second;
                // //this determine the resources
                this->resources = this->target.substr(confLocation.length());
                // std::cout << resources << "p\n";
                return true;
            }
        }
        // break;
        std::cout << "\n";
    }
    return false;
}

bool    HttpRequestChecker::checkLocationHasRedirection() {
    //check if the location have a redirection like return 301 /home/index.html
    // std::cout << location["redirect"] << "----\n";
    if (!this->location["redirect"].empty() && this->location["redirect"] != "none")
        return true;
    return false;
}

bool    HttpRequestChecker::checkMethodAllowed(std::string &allowedMethod) {
    if (location["method1"] == method || location["method2"] == method || location["method3"] == method || method == "HEAD")
        return true;
    allowedMethod += location["method1"] != "none" ? location["method1"]: "";
    allowedMethod += location["method2"] != "none" ? ", " + location["method2"] : "";
    allowedMethod += location["method3"] != "none" ? ", " + location["method3"] : "";
    return false;
}




//check if the content is exist in in root
bool    HttpRequestChecker::checkContentExistsInRoot() {
    this->resourcesWithPath = location["root"] + this->resources;
    // std::cout << "resources with path: " << resourcesWithPath << std::endl;
    // std::cout << "path: " << resourcesWithPath << std::endl;
    if (access(this->resourcesWithPath.c_str(), F_OK) == 0)
        // std::cout << "kayna a3shiri: " << resourcesWithPath << std::endl;
        return true;
    return false;
}

bool    HttpRequestChecker::checkContentIsDir() {
    struct stat statBuf;
    if (stat(this->resourcesWithPath.c_str(), &statBuf) != 0)
    {
        std::cout << "error in stat\n";
        return false;
    }
    return S_ISDIR(statBuf.st_mode);
}

//check if the directory has an index file
bool    HttpRequestChecker::checkIndexFilesInDir() {
    //first check if there is index in conf
        //in case is exist check if it's exist in dir
        //else: check if there is index.html in directory
    std::string indexFromConf = location["index"];
    // std::cout << "[[" << this->resourcesWithPath + indexFromConf << "]]\n";
    // std::cout << "checkIndexFilesInDir() -- " << this->resourcesWithPath + indexFromConf << std::endl;
    //change resource path
    if (!indexFromConf.empty()) {
        if (access((this->resourcesWithPath + indexFromConf).c_str(), F_OK))
            return false;
    }
    if (access((this->resourcesWithPath + "index.html").c_str(), F_OK))
        return false;
    this->resourcesWithPath = this->resourcesWithPath + indexFromConf;
    return true;
}

bool    HttpRequestChecker::checkAutoIndexOn() {
    //check if the index file is on
    return true;
}

bool    HttpRequestChecker::checkLocationIncludesCgi() {
    //check if the location include cgi configurations
    return false;
}

bool    HttpRequestChecker::checkDirIndedWithBackSlash() {
    return this->resourcesWithPath.at(this->resourcesWithPath.length() - 1) == '/';
}
