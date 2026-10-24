#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/ip.h> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

// This is the code for the client to create a connecting socket
void ConnectingSocket()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);;
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);
    int rv = connect(fd, (const struct sockaddr*)&addr, sizeof(addr));
    if (rv == -1) {
        perror("connect");
        close(fd);
        return;
    }
    char msg[] = "Hello There";
    // Send the message using write
    ssize_t written = write(fd, msg, strlen(msg));
    if (written == -1) {
        perror("write");
    }

    char rbuf[64] = {};
    ssize_t n = read(fd, rbuf, sizeof(rbuf) - 1);
    if (n < 0) {
        perror("read");
        close(fd);
        return;
    }
    printf("server says %s\n", rbuf);
    close(fd);
}

int main() {
    ConnectingSocket();
}