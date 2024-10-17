#include <arpa/inet.h>
#include <inttypes.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 256
#define LOCAL_HOST "127.0.0.1"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <port>", argv[0]);
        return -1;
    }

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int port = strtoimax(argv[1], NULL, 10);

    struct sockaddr_in sockaddr;
    inet_aton(LOCAL_HOST, &(sockaddr.sin_addr));
    sockaddr.sin_port = htons(port);
    sockaddr.sin_family = AF_INET;

    // char buf[MAX_BUFFER_SIZE];
    // inet_ntop(AF_INET, &sockaddr.sin_addr, buf, MAX_BUFFER_SIZE);
    // printf("address: %s\n", buf);
    // printf("port: %d\n", ntohs(sockaddr.sin_port));

    // Create socket
    //
    int listener_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener_fd < 0) {
        printf("Error creating socket: %d.\n", listener_fd);
        return -1;
    }

    struct addrinfo *res;
    int error = getaddrinfo("localhost", NULL, &hints, &res);
    if (error < 0) {
        close(listener_fd);
        printf("Error getting address info: %d.\n", error);
        return -1;
    }

    // Bind to localhost on the given port
    //
    error = bind(listener_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));  // TODO: Why do we use sizeof sockaddr as the length?
    if (error < 0) {
        close(listener_fd);
        printf("Error binding to address: %d.\n", error);
        return -1;
    }

    // Listen for connections
    //
    error = listen(listener_fd, 50);
    if (error < 0) {
        close(listener_fd);
        printf("Error listening on port: %d\n", error);
        return -1;
    }

    printf("Listening on port: %d\n", port);
    fflush(stdout);

    struct sockaddr_in peer_addr;
    socklen_t peer_addr_len;
    int fd = accept(listener_fd, (struct sockaddr *)&peer_addr, &peer_addr_len);
    if (fd < 0) {
        close(listener_fd);
        printf("Error accepting connection.");
        return -1;
    }

    char buf[MAX_BUFFER_SIZE];

    struct sockaddr_in sin = (struct sockaddr_in *)&addr;

    inet_ntop(AF_INET, &addr.sa_data, buf, addr.sa_len);
    printf("Accepted connection from %s\n", buf);

    char msg[MAX_BUFFER_SIZE];
    read(fd, msg, MAX_BUFFER_SIZE);

    printf("Received Message: %s\n", msg);

    close(listener_fd);

    return 0;
}