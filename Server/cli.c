#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 256
#define DECORATOR "> "

// CLI
// I need an interface for registering server commands
// I need a mapping of strings to functions
// All of the functoins will abide by an interface
// What commands do I want?
// start <port>
// stop
// help
// quit
// broadcast <msg> (it would be cool to send a message to all of the clients)

int main(void) {
    while (1) {
        char buf[MAX_BUFFER_SIZE];
        printf(DECORATOR);
        fgets(buf, MAX_BUFFER_SIZE, stdin);
        printf("%s\n", buf);

        // parse

        // handle
    }
}