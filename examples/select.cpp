#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

int main() {
    fd_set rd;
    struct timeval tv;
    int err;

    FD_ZERO(&rd);
    FD_SET(0, &rd);
    

    tv.tv_sec = 2;
    tv.tv_usec = 0;
    // while(true) {
        err = select(1, &rd, NULL, NULL, &tv);
        if (err == 0) {
        std::cout << "select error\n";
        }
        else if (err == 0) {
            std::cout << "timeout\n";
        }
        else {
            std::cout << "data is available\n";
        }
    // }
    return 0;
}