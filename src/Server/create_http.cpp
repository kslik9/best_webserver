
#include "webserv.hpp"


std::string Server::buildHttpResponse(int socketIndex, std::string requestStr, int bodySize)
{
	// std::cout << GREEN_TEXT << "final_res: " << "[" << requestStr << "]" << RESET_COLOR << std::endl;
    std::string php_resp;
    // ------------------------------------------
    RequestData request(requestStr);
    // // ------------------------------------------
    AResponseMessage *createdResponse;
    std::string     responseMessage;
    //http request checker
    HttpRequestFlow  hm(request, conf.at(socketIndex));

    hm.setBodySize(bodySize);
    createdResponse = hm.checkRequestAndReturnHttpMessage();
    responseMessage = createdResponse->createResponse();
    
    delete createdResponse;
    return responseMessage;
}
