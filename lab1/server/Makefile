
CC=gcc
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c -Wall

all: server

server: server.o
	$(CC) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c

clean:
	rm -rf *.o server
