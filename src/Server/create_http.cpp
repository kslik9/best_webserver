
#include "webserv.hpp"


std::string Server::buildHttpResponse(std::string requestStr, short socketIndex, int contentLen)
{
	// std::cout << GREEN_TEXT << "final_res: " << "[" << requestStr << "]" << RESET_COLOR << std::endl;

    std::cout << "sockIndex: " << socketIndex << std::endl;
    int         fileStat;
    std::string php_resp;
    // ------------------------------------------
    RequestData request(requestStr);
    // // ------------------------------------------
    AResponseMessage *createdResponse;
    std::string     responseMessage;

    //http request checker
    HttpRequestFlow  hm(request, conf.at(socketIndex));
    if (request.getMethod() == "POST")
        hm.setContentLen(contentLen);
    createdResponse = hm.checkRequestAndReturnHttpMessage();
    responseMessage = createdResponse->createResponse();

    
    delete createdResponse;
    return responseMessage;

}
