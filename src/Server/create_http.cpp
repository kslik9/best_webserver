
#include "webserv.hpp"

std::map<std::string, std::string> init_mime_types()
{
    std::map<std::string, std::string> mime_types;

    // Define your MIME type mappings in a loop
    mime_types[".html"] = "text/html";
    mime_types[".htm"] = "text/html";
    mime_types[".shtml"] = "text/html";
    mime_types[".css"] = "text/css";
    mime_types[".js"] = "application/javascript";
    mime_types[".json"] = "application/json";
    mime_types[".xml"] = "application/xml";
    mime_types[".txt"] = "text/plain";
    mime_types[".jpg"] = "image/jpeg";
    mime_types[".jpeg"] = "image/jpeg";
    mime_types[".png"] = "image/png";
    mime_types[".gif"] = "image/gif";
    mime_types[".bmp"] = "image/bmp";
    mime_types[".svg"] = "image/svg+xml";
    mime_types[".pdf"] = "application/pdf";
    mime_types[".doc"] = "application/msword";
    mime_types[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mime_types[".xls"] = "application/vnd.ms-excel";
    mime_types[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mime_types[".ppt"] = "application/vnd.ms-powerpoint";
    mime_types[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mime_types[".zip"] = "application/zip";
    mime_types[".tar"] = "application/x-tar";
    mime_types[".gz"] = "application/gzip";
    mime_types[".mp3"] = "audio/mpeg";
    mime_types[".wav"] = "audio/wav";
    mime_types[".ogg"] = "audio/ogg";
    mime_types[".mp4"] = "video/mp4";
    mime_types[".avi"] = "video/x-msvideo";
    return mime_types;
}

static std::map<std::string, std::string> mime_types = init_mime_types();

std::string get_mime_type(const std::string &fileName)
{
    size_t dotPosition = fileName.find_last_of('.');
    if (dotPosition != std::string::npos)
    {
        std::string fileExtension = fileName.substr(dotPosition);
        std::map<std::string, std::string>::iterator it = mime_types.find(fileExtension);
        if (it != mime_types.end())
        {
            return it->second;
        }
    }
    return "application/octet-stream"; // Default MIME type
}

std::string not_found_404()
{
    return "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
}

std::string forbidden_403()
{
    return "HTTP/1.1 403 Forebidden\r\nContent-Type: text/html\r\n\r\n<h1>403 Forbidden</h1>";
}





//400 Bad Request
bool check400(std::string &target) {
	std::string allowedChars  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	unsigned int	targetLen = target.length();

	// std::cout << "target : " << target << std::endl;
	for (int i = 1; i < targetLen; i++) {
		if (allowedChars.find(target[i]) == std::string::npos)
			return true;
	}
	return false;
}

//414 URI Too Long
bool check414(std::string &target) {
	if (target.length() > 2048)
		return true;
	return false;
}

bool check404(std::string &target, int stat) {
    //check if no location matches the target
    //.
    //.
    //.
    //.

    //check if requested resourse not found in root
    if (access((STATIC_HTTP + target).c_str(), F_OK))
        return true;
    return false;
}

bool check301() {
    //here we will check if the location has redirection
    //solved l8r
    return false;
}

bool check405(std::string &method) {
    //here we check if the target resource does'nt support this method
    //solved l8r
    return false;
}

bool isTargetDir(std::string &target) {
    //check if target a dirctory
    if (target[target.length() - 1] == '/')
        return true;
    return false;
}
bool isDirHasIndexFile(std::string &target) {
    return true;
}

bool autoIndexOff(std::string &target) {
    return false;
}

bool LocationIncludesCgi() {
    return false;
}
#define NO_LOCATION_MATCHES_TARGET 1
#define RESOURCE_NOT_FOUND_IN_ROOT 2

void	checkRequest(std::string &method, std::string &target) {
	if(check400(target))
		std::cout << "400 Bad Request\n";
	else if(check414(target))
		std::cout << "414 URI Too Long\n";
	else if(check404(target, NO_LOCATION_MATCHES_TARGET))
        std::cout << "404 Not Found\n";
    else if(check301())
        std::cout << "redirection\n";
    else if (check405(method))
        std::cout << "405 Method Not Allowed\n";
    else if (method == "GET") {
        if (check404(target, RESOURCE_NOT_FOUND_IN_ROOT))
            std::cout << "404 Not Found\n";
        //check resourses type if is dir ...
        if (isTargetDir(target)) {
            //check if this directory has an index file (eg: index.html)
            if (!isDirHasIndexFile(target)) {
                //check autoindex off
                if (autoIndexOff(target))
                    std::cout << "403 Forbidden\n";
                else
                    //return autoindex of the directory
                    std::cout << "200 OK\n";
            }
        }
        // else if it's file
        else {
            if (LocationIncludesCgi()) {
                //run cgi on requested file
                //return code depend on cgi
            }
            else {
                // return the file
                std::cout << "200 OK\n";
            }
        }
    }
}


std::string buildHttpResponse(std::string __unused &method, std::string &target, ReturnStatus &rs)
{
    int fileStat;

    if (target == "/")
        target = "index.html";
    std::string mime_type = get_mime_type(target), response;
    std::stringstream header;
    header << "HTTP/1.1 200 OK\r\n"
           << "Content-Type: " << mime_type << "\r\n"
           << "\r\n";
    response = header.str();
    fileStat = access((STATIC_HTTP + target).c_str(), F_OK);


    checkRequest(method, target);

    if (access((STATIC_HTTP + target).c_str(), F_OK))
        return rs.notFound_404();
    else if (access((STATIC_HTTP + target).c_str(), R_OK))
        return rs.forbidden_403();
    //open the file
    std::ifstream file((STATIC_HTTP + target).c_str(), std::ios::binary);
    if (!file.is_open())
        return rs.notFound_404();
    std::ostringstream fileContent;
    fileContent << file.rdbuf();
    response += fileContent.str();
    // response += execute_php("php/index.php"); // CGI
    return response;
}
