
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

// This is the code for the server to create a listening socket
void ListenSocket()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    bind(fd, port);
    listen(fd)
    while True:
        conn_fd(accept(fd))
        do_something_with(conn_fd)
        close(conn_fd)
}