CC 		= gcc
CFLAGS 	= -g
RM 		= rm -rf

default: all

all: main cli strtoktest

main: main.c
	$(CC) $(CFLAGS) main.c -o ./build/main.out

cli: cli.c
	$(CC) $(CFLAGS) cli.c -o ./build/cli.out

strtoktest: strtoktest.c
	$(CC) $(CFLAGS) strtoktest.c -o ./build/strtoktest.out

clean:
	$(RM) ./build/*