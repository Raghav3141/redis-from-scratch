
char *sample_message = "Hello There"; 

// This is the code for the client to create a connecting socket
void ConnectingSocket()
{
    int fd = socket();
    connect(fd, address);
    do_something_with(fd);
    close(fd);
}