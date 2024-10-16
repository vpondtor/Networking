#include <arpa/inet.h>
#include <inttypes.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 256

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <port>", argv[0]);
        return -1;
    }

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_addrlen = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int port = strtoimax(argv[1], NULL, 10);

    struct sockaddr_in sockaddr;
    inet_aton("127.0.0.1", &(sockaddr.sin_addr));
    sockaddr.sin_port = htons(port);
    sockaddr.sin_family = AF_INET;

    // char buf[MAX_BUFFER_SIZE];
    // inet_ntop(AF_INET, &sockaddr.sin_addr, buf, MAX_BUFFER_SIZE);
    // printf("address: %s\n", buf);
    // printf("port: %d\n", ntohs(sockaddr.sin_port));

    int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd < 0) {
        printf("Socket could not be created.\n");
        return -1;
    }

    int error = getaddrinfo("localhost", NULL, &hints, &res);
    if (error < 0) {
        close(fd);
        printf("Could not get addr info.\n");
    }

    for (; res != NULL; res = res->ai_next) {
        error = bind(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));  // Why do we use sizeof sockaddr as the length?
        if (error < 0) {
            continue;
        }

        break;
    }

    if (error < 0) {
        close(fd);
        printf("Could not bind to address with given socket.");
        return -1;
    };

    printf("Listening on port: %d\n", port);
    error = listen(fd, 50);  // Why is this 50? It's the backlog. The amt that
                             // can be in the queue
    if (error < 0) {
        close(fd);
        printf("Could not listen on socket.");
        return -1;
    }

    fflush(stdout);
    struct sockaddr client_addr;
    socklen_t client_addr_len;
    int newsocket_fd = accept(fd, &client_addr, &client_addr_len);
    if (newsocket_fd < 0) {
        close(fd);
        printf("Error accepting connection.");
        return -1;
    }

    struct sockaddr_in *sin = (struct sockaddr_in *)&client_addr;
    char buf[MAX_BUFFER_SIZE];

    inet_ntop(AF_INET, &sin->sin_addr, buf, INET_ADDRSTRLEN);
    printf("Accepted connection from %s:%d\n", buf, ntohs(sin->sin_port));  // I don't think this is right

    char msg[MAX_BUFFER_SIZE];
    read(newsocket_fd, msg, MAX_BUFFER_SIZE);

    printf("Received Message: %s\n", msg);

    close(fd);

    return 0;
}