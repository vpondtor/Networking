#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define DELIMITER " "

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage %s <string>", argv[0]);
        return 1;
    }

    char* test = argv[1];

    for (char* word = strtok(test, DELIMITER); word; word = strtok(NULL, DELIMITER)) {
        printf("%s\n", word);
    }

    return 0;
}