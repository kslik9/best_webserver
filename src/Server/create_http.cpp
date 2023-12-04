
#include "webserv.hpp"

// std::map<std::string, std::string> init_mime_types()
// {
//     std::map<std::string, std::string> mime_types;

//     // Define your MIME type mappings in a loop
//     mime_types[".html"] = "text/html";
//     mime_types[".htm"] = "text/html";
//     mime_types[".shtml"] = "text/html";
//     mime_types[".css"] = "text/css";
//     mime_types[".js"] = "application/javascript";
//     mime_types[".json"] = "application/json";
//     mime_types[".xml"] = "application/xml";
//     mime_types[".txt"] = "text/plain";
//     mime_types[".jpg"] = "image/jpeg";
//     mime_types[".jpeg"] = "image/jpeg";
//     mime_types[".png"] = "image/png";
//     mime_types[".gif"] = "image/gif";
//     mime_types[".bmp"] = "image/bmp";
//     mime_types[".svg"] = "image/svg+xml";
//     mime_types[".pdf"] = "application/pdf";
//     mime_types[".doc"] = "application/msword";
//     mime_types[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
//     mime_types[".xls"] = "application/vnd.ms-excel";
//     mime_types[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
//     mime_types[".ppt"] = "application/vnd.ms-powerpoint";
//     mime_types[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
//     mime_types[".zip"] = "application/zip";
//     mime_types[".tar"] = "application/x-tar";
//     mime_types[".gz"] = "application/gzip";
//     mime_types[".mp3"] = "audio/mpeg";
//     mime_types[".wav"] = "audio/wav";
//     mime_types[".ogg"] = "audio/ogg";
//     mime_types[".mp4"] = "video/mp4";
//     mime_types[".avi"] = "video/x-msvideo";
//     return mime_types;
// }

// static std::map<std::string, std::string> mime_types = init_mime_types();

// std::string get_mime_type(const std::string &fileName)
// {
//     size_t dotPosition = fileName.find_last_of('.');
//     if (dotPosition != std::string::npos)
//     {
//         std::string fileExtension = fileName.substr(dotPosition);
//         std::map<std::string, std::string>::iterator it = mime_types.find(fileExtension);
//         if (it != mime_types.end())
//         {
//             return it->second;
//         }
//     }
//     return "application/octet-stream"; // Default MIME type
// }

// std::string not_found_404()
// {
//     return "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
// }

// std::string forbidden_403()
// {
//     return "HTTP/1.1 403 Forebidden\r\nContent-Type: text/html\r\n\r\n<h1>403 Forbidden</h1>";
// }


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


// --------------------------------------------
// POST /upload.php HTTP/1.1
// Host: localhost:8080
// User-Agent: curl/7.64.1
// Accept: */*
// Content-Length: 27
// Content-Type: application/x-www-form-urlencoded
// 
// param1=value1&param2=value2
// --------------------------------------------

// #include "HttpMessage.hpp"
// std::string Server::buildHttpResponse(std::string &method, std::string &target)
std::string Server::buildHttpResponse(int socketIndex, std::string requestStr)
{
    int         fileStat;

    // std::cout << "socket index: " << socketIndex << std::endl;




    //request data
    RequestData         request(requestStr);

    CGIHandler  handler(request);

    std::string c = handler.process();
    std::cout << c << std::endl;
    return "NULL";

    AResponseMessage    *createdResponse;
    std::string         responseMessage;
    //http request checker
    HttpRequestChecker  hm(request, conf.at(socketIndex));
    createdResponse = hm.checkRequestAndReturnHttpMessage();
    responseMessage = createdResponse->createResponse();
    delete createdResponse;
    return responseMessage;
}
