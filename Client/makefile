CC 		= gcc
CFLAGS 	= -g
RM 		= rm -rf

default: all

all: main

main: main.c
	$(CC) $(CFLAGS) main.c -o ./build/main.out

test: test.c
	$(CC) $(CFLAGS) test.c -o ./build/test.out

clean:
	$(RM) ./build/*