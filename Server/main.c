#include <arpa/inet.h>
#include <inttypes.h>
#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 256
#define LOCAL_HOST "127.0.0.1"

static void *accept_connections(void *arg) {
    int listener_fd = *((int *)arg);
    int count = 0;
    while (1) {
        int fd = accept(listener_fd, NULL, NULL);
        if (fd < 0) {
            close(fd);
            printf("Error accepting connection: %d\n", fd);
            return NULL;
        }

        // TODO: Print out the IP of the incoming connection;
        printf("Accepted a new connection: %d\n", count++);
    }

    return NULL;
}

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

    // Bind to the given address
    //
    error = bind(listener_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
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

    pthread_t thread;
    pthread_create(&thread, NULL, accept_connections, &listener_fd);

    // TODO: Don't just join this. Have a command line interface or do some signal processing
    // to clean this up
    pthread_detach(thread, NULL);

    close(listener_fd);

    return 0;
}