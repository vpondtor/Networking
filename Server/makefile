CC 		= gcc
CFLAGS 	= -g
RM 		= rm -rf

default: all

all: main cli

main: main.c
	$(CC) $(CFLAGS) main.c -o ./build/main.out

cli: cli.c
	$(CC) $(CFLAGS) cli.c -o ./build/cli.out

clean:
	$(RM) ./build/*