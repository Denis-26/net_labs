
CC=gcc
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c -Wall

all: client

client: client.o
	$(CC) client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) client.c

clean:
	rm -rf *.o client
