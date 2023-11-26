#include "HttpResponseMsgCreator.hpp"

HttpResponseMsgCreator::HttpResponseMsgCreator(RequestData &request) {
    // this->request = request;
    // this->statusCode = statusCode;
    // this->statusMessage = statusMessage;
    std::cout << "[" << request.getUri() << "]" << std::endl;
    std::cout << "[" << request.getMethod() << "]" << std::endl;
}