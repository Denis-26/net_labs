
CC=gcc
CFLAGS=-c

all: client

client: client.o
	$(CC) client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) client.c

clean:
	rm -rf *.o client
