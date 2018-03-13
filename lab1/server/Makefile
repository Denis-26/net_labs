
CC=gcc
CFLAGS=-c

all: server

server: server.o
	$(CC) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c

clean:
	rm -rf *.o server
