#include "HttpRequestFlow.hpp"

bool    HttpRequestFlow::checkNotAllowededChars() {
    std::string allowedChars  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	unsigned int	targetLen = target.length();

	for (int i = 1; i < targetLen; i++) {
		if (allowedChars.find(target.at(i)) == std::string::npos)
			return true;
	}
	return false;
}

bool    HttpRequestFlow::checkUriLength() {
    if (target.length() > 2048)
		return true;
	return false;
}

bool    HttpRequestFlow::checkRequestHttpMessage() {
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
bool    HttpRequestFlow::checkLocationMatchRequestUri() {

    std::string confLocation;
    std::list<std::string> extractedRoutes;
    std::string stringRoute;

    stringRoute = getRouteStr(target);
    extractedRoutes = extractRoutes(stringRoute);

    //iterate until finding a match location
    for (std::list<std::string>::iterator extractedRoutesIt = extractedRoutes.begin(); extractedRoutesIt != extractedRoutes.end(); ++extractedRoutesIt) {
        for (std::map<std::string, mp>::iterator locationsIt = config.rout.begin(); locationsIt != config.rout.end(); ++locationsIt) {
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

bool    HttpRequestFlow::checkLocationHasRedirection() {
    //check if the location have a redirection like return 301 /home/index.html
    // std::cout << location["redirect"] << "----\n";
    if (!this->location["redirect"].empty() && this->location["redirect"] != "none")
        return true;
    return false;
}

bool    HttpRequestFlow::checkMethodAllowed(std::string &allowedMethod) {
    if (location["method1"] == method || location["method2"] == method || location["method3"] == method || method == "HEAD")
        return true;
    allowedMethod += location["method1"] != "none" ? location["method1"]: "";
    allowedMethod += location["method2"] != "none" ? ", " + location["method2"] : "";
    allowedMethod += location["method3"] != "none" ? ", " + location["method3"] : "";
    return false;
}




//check if the content is exist in in root
bool    HttpRequestFlow::checkContentExistsInRoot() {
    this->resourcesWithRoot = this->location["root"] + this->resources;
    // std::cout << "rw: " << this->resourcesWithRoot << std::endl;
    // std::cout << "r : " << this->resources << std::endl;
    // std::cout << "ta: " << this->target << std::endl;

    if (access(this->resourcesWithRoot.c_str(), F_OK) == 0)
        return true;
    return false;
}

bool    HttpRequestFlow::checkContentIsDir() {
    struct stat statBuf;
    if (stat(this->resourcesWithRoot.c_str(), &statBuf) != 0)
    {
        std::cout << "error in stat\n";
        return false;
    }
    return S_ISDIR(statBuf.st_mode);
}

//check if the directory has an index file
bool    HttpRequestFlow::checkIndexFilesInDir() {
    //first check if there is index in conf
        //in case is exist check if it's exist in dir
        //else: check if there is index.html in directory
    std::string indexFromConf = location["index"];
    // std::cout << "index: " << indexFromConf << std::endl;
    // std::cout << "[[" << this->resourcesWithRoot + indexFromConf << "]]\n";
    // std::cout << "checkIndexFilesInDir() -- " << this->resourcesWithRoot + indexFromConf << std::endl;
    //change resource path
    if (!indexFromConf.empty() && indexFromConf != "off" && indexFromConf != "on") {
        if (access((this->resourcesWithRoot + indexFromConf).c_str(), F_OK))
            return false;
        this->resourcesWithRoot = this->resourcesWithRoot + indexFromConf;
        return true;
    }
    if (!access((this->resourcesWithRoot + "index.html").c_str(), F_OK))
    {
        this->resourcesWithRoot = this->resourcesWithRoot + "index.html";
        return true;
    }
    return false;
}

//check if autoindex file is on
bool    HttpRequestFlow::checkAutoIndexOn() {
    return location["autoindex"] == "on";
}

bool    HttpRequestFlow::checkLocationIncludesCgi() {
    if (this->resourcesWithRoot.substr(this->resourcesWithRoot.length() - 4) != ".php")
        return false;
    if (this->location["cgi_extension"] != "none" && this->location["cgi_extension"] == ".php")
        return true;
    return false;
}

bool    HttpRequestFlow::checkDirIndedWithBackSlash() {
    return this->resourcesWithRoot.at(this->resourcesWithRoot.length() - 1) == '/';
}

bool    HttpRequestFlow::checkLocationSupportUpload() {
    return true;
}

bool    HttpRequestFlow::deleteDirContent() {
    std::cout << this->resourcesWithRoot << "d" << std::endl;
    return true;
}

bool    HttpRequestFlow::checkWriteAccessOnDir() {
    return false;
}

bool    HttpRequestFlow::deleteFile() {
    return true;
}

bool    HttpRequestFlow::fileExceedsMaxSize() {
    return false;
}