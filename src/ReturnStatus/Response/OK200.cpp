#include "OK200.hpp"

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

OK200::OK200(std::string &resource) {
    this->statusCode = "200";
    this->statusMessage = "OK";
    this->resourcePath = resource;
    this->headers["Content-Type"] = get_mime_type(resource);
    this->headers["Date"] = getCurrentTime();
}

std::string OK200::createResponse() {
    startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";

    std::map<std::string, std::string>::iterator it;
    response << startLine;
    for (it = headers.begin(); it != headers.end(); ++it)
        response << it->first << ": " << it->second << "\r\n";
    response << "\r\n";


    //create body
    std::ifstream file1(this->resourcePath, std::ios::binary);
    std::ostringstream fileContent;
    fileContent << file1.rdbuf();
    response << fileContent.str();
    return response.str();
}