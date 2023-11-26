
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


// #include "HttpMessage.hpp"
// std::string Server::buildHttpResponse(std::string &method, std::string &target)
std::string Server::buildHttpResponse(std::string request)
{
    int         fileStat;

    //request data
    RequestData rd(request);

    //http meassage
    HttpMessageChecker hm(rd, config);

    hm.checkRequestAndReturnHttpMessage();



    // if (target == "/")
    //     target = "index.html";
    // std::string mime_type = get_mime_type(target), response;
    // std::stringstream header;
    // header << "HTTP/1.1 200 OK\r\n"
    //        << "Content-Type: " << mime_type << "\r\n"
    //        << "\r\n";
    // response = header.str();
    // fileStat = access((STATIC_HTTP + target).c_str(), F_OK);

    // HttpMessage.createHttpHeader();

    // checkRequestAndReturnHttpMessage(method, target);

    // if (access((STATIC_HTTP + target).c_str(), F_OK))
    //     return rs.notFound_404();
    // else if (access((STATIC_HTTP + target).c_str(), R_OK))
    //     return rs.forbidden_403();
    // //open the file
    // std::ifstream file((STATIC_HTTP + target).c_str(), std::ios::binary);
    // if (!file.is_open())
    //     return rs.notFound_404();
    // std::ostringstream fileContent;
    // fileContent << file.rdbuf();
    // response += fileContent.str();
    // response += execute_php("php/index.php"); // CGI
    std::string response;
    return response;
}
