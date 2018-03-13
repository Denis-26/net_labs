
CC=gcc
CFLAGS=-c -std=c99 -Wall

all: server

server: server.o
	$(CC) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c

clean:
	rm -rf *.o server
