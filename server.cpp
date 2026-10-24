#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/ip.h> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void do_something_with_client(int client_fd) {
    char rbuf[64] = {};
    ssize_t n = read(client_fd, rbuf, sizeof(rbuf) - 1);
    if (n < 0) {
        std::exit(EXIT_FAILURE);
        return;
    }
    // Process the received data
    printf("client says %s\n", rbuf);

    char wbuf[64] = "hello client";
    ssize_t written = write(client_fd, wbuf, strlen(wbuf));
    if (written == -1) {
        perror("write");
    }
}

// This is the code for the server to create a listening socket
void ListenSocket(uint32_t ip, uint16_t port)
{
    // We will use IPv4 socket to listen for incoming connections
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(ip);
    int rv = bind(fd, (const struct sockaddr*)&addr, sizeof(addr));
    // When we listen to the socket, we will just use the maximum communication queue size of 4096 bytes
    rv = listen(fd, SOMAXCONN);
    if (rv) {
        std::exit(EXIT_FAILURE);
    }
    while (true){
        struct sockaddr_in client_addr = {};
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            // Handle error
            continue;
        }
        do_something_with_client(client_fd);
        close(client_fd);
    }
}

int main() {
    ListenSocket(INADDR_ANY, 1234);
}
