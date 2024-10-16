#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX_BUFFER_SIZE 256

void print_family(struct addrinfo *info) {
    printf("family: ");
    switch (info->ai_family) {
        case PF_LOCAL:
            printf("local ");
            break;
        case PF_INET:
            printf("ipv4 ");
            break;
        case PF_INET6:
            printf("ipv6 ");
            break;
        default:
            printf("unknown ");
            break;
    }
}

void print_type(struct addrinfo *info) {
    printf("type: ");
    switch (info->ai_socktype) {
        case SOCK_STREAM:
            printf("stream ");
            break;
        case SOCK_DGRAM:
            printf("dgram ");
            break;
        case SOCK_RAW:
            printf("raw ");
            break;
        case SOCK_RDM:
            printf("rdm ");
            break;
        case SOCK_SEQPACKET:
            printf("seqpacket ");
            break;
        default:
            printf("unknown ");
            break;
    }
}

void print_protocol(struct addrinfo *info) {
    printf("protocol: ");
    switch (info->ai_protocol) {
        case IPPROTO_TCP:
            printf("tcp ");
            break;
        case IPPROTO_UDP:
            printf("udp ");
            break;
        case IPPROTO_RAW:
            printf("raw ");
            break;
        default:
            printf("unknown ");
            break;
    }
}

void print_addrinfo(struct addrinfo *info) {
    printf("\n");
    print_family(info);
    print_type(info);
    print_protocol(info);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <hostname> <service>", argv[0]);
    }

    if (strcmp(argv[1], "NULL") == 0) {
        argv[1] = NULL;
    }

    if (strcmp(argv[2], "NULL") == 0) {
        argv[2] = NULL;
    }

    int fd;
    char buffer[MAX_BUFFER_SIZE];
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_addrlen = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int error = getaddrinfo(argv[1], argv[2], &hints, &res);
    if (error < 0) {
        printf("Could not get addr info.\n");
        return error;
    }

    for (; res != NULL; res = res->ai_next) {
        print_addrinfo(res);

        // why can't these ne created in the switch?
        //
        char buf[INET_ADDRSTRLEN];
        struct sockaddr_in *sinp;
        struct sockaddr_in6 *sinp6;
        const char *addr;

        printf("\n\t");
        switch (res->ai_family) {
            case AF_INET:
                printf("inet ");
                sinp = (struct sockaddr_in *)res->ai_addr;
                addr = inet_ntop(AF_INET, &sinp->sin_addr, buf, INET_ADDRSTRLEN);
                printf("address: %s ", addr);
                printf("port: %d", ntohs(sinp->sin_port));
                break;
            case AF_INET6:
                printf("inet6 ");
                sinp6 = (struct sockaddr_in6 *)res->ai_addr;
                addr = inet_ntop(AF_INET6, &sinp6->sin6_addr, buf, INET6_ADDRSTRLEN);
                printf("address: %s ", addr);
                printf("port: %d", ntohs(sinp6->sin6_port));
                break;

            default:
                break;
        }
    }

    return 0;
}