#include "AResponseMessage.hpp"

std::string getCurrentTime() {
    std::time_t currentTime = std::time(0);
    std::tm* timeInfo = std::gmtime(&currentTime);

    char buffer[80];
    std::strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
    // std::cout << "time " << buffer;
    return buffer;
}