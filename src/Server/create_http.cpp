
#include "webserv.hpp"



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
	// std::cout << GREEN_TEXT << "final_res: " << "[" << requestStr << "]" << RESET_COLOR << std::endl;

    int         fileStat;
    std::string php_resp;
    // // ------------------------------------------
    php_resp += "HTTP/1.1 200 OK\r\n";
    php_resp += "Content-Type: text/html\r\n";
    // ------------------------------------------
    RequestData request(requestStr);
    // std::cout << "something her2\n";
    AResponseMessage *createdResponse;
    std::string     responseMessage;
    //http request checker
    HttpRequestFlow  hm(request, conf.at(socketIndex));
    createdResponse = hm.checkRequestAndReturnHttpMessage();
    responseMessage = createdResponse->createResponse();
    
    delete createdResponse;
    return responseMessage;
    // std::cout << "something her2\n";

    return php_resp;
}

    
    // system("clear");
    // std::cout << "------------------------------------------------------\n";
    // CGIHandler handler(request);
    // std::string resp = handler.process();
    // php_resp += resp;
    // return php_resp;