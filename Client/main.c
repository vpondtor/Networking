#include <arpa/inet.h>
#include <inttypes.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <port>", argv[0]);
        return -1;
    }

    int port = strtoimax(argv[1], NULL, 10);

    int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd < 0) {
        printf("Could not create socket.");
        return -1;
    }

    struct sockaddr_in target_addr;
    inet_aton("127.0.0.1", &target_addr.sin_addr);
    target_addr.sin_port = htons(port);  // Host to network
    target_addr.sin_family = AF_INET;

    if (connect(fd, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0) {
        printf("Client could not connect to socket.");
        close(fd);
        return -1;
    }

    char msg[] = "Hello World";
    if (send(fd, msg, sizeof(msg), 0) < 0) {
        close(fd);
        printf("Couldn't send msg.");
        return -1;
    }  // I forgot the nuances of sizeof

    printf("Message sent");

    close(fd);
    return (0);
}