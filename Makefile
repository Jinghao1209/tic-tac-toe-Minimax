CC=gcc

# use `./main` to run
all: main

main: main.c
	$(CC) main.c -o main