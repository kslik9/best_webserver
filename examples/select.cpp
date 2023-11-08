#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <memory>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string>
#include <map>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <signal.h>
#include <poll.h>
#include <termios.h>

int main() {

    //Set up a non-blocking read from stdin(chatgpt)
    struct termios orig_term, new_term;
    int saved_flags;

    tcgetattr(STDIN_FILENO, &orig_term);
    new_term = orig_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    saved_flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, saved_flags | O_NONBLOCK);


    struct pollfd fds[2];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    fds[1].fd = open("file1", O_RDONLY);
    fds[1].events = POLLIN;

    
    //3 seconds
    int timeout = 5000;

    int retval = poll(fds, 2, timeout);
    while (true)
    {
         if (retval == -1)
            perror("poll");
        else if (retval == 0)
            std::cout << "timeout \n";
        else {
            if (fds[0].revents == POLLIN) {
                printf("afin a tffa7 lmrta7 - 1\n");
            }
            if (fds[1].revents == POLLIN) {
                printf("afin a tffa7 lmrta7 - 2\n");
            }
        }
    }
    



//      struct pollfd struct_fds[2];

//     int fd;

//     fd = open(0, O_RDONLY);
//     struct_fds[0].fd = fd;
//     fd = open(0, O_RDONLY);
//     struct_fds[1].fd = fd;

//     struct_fds[0].events = POLLIN;
//     struct_fds[1].events = POLLIN;

//     poll(struct_fds, 2, 0);

    
// if ( struct_fds[0].revents ==  POLLOUT)
//      printf("The file1 can accept write operations.\n");
// else
//     {
//      printf("The file1 cannot accept write operations.\n" );
//      printf("file1 revents = %i\n", struct_fds[0].revents );
//      }
// if ( struct_fds[1].revents == POLLOUT)
//      printf("The file2 can accept write operations.\n" );
// else
//     {
//      printf("The file2 cannot accept write operations.\n" );
//      printf("file2 revents = %i\n", struct_fds[1].revents );
//     }
//     //Step 6
//     sleep (3);
//     close (struct_fds[0].fd);
//     close (struct_fds[1].fd);
}