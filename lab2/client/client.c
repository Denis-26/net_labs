#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <netinet/in.h>

#define BUFLEN 512

void die(char *s){
    perror(s);
    exit(1);
}
struct proto{
    unsigned short id;
    short flag;
    char buf[BUFLEN];
};

int inet_aton(const char *cp, struct in_addr *inp);

int main(int argc, char *argv[]){
  const int PORT = strtol(argv[1], NULL, 10);
  struct sockaddr_in saddr_server = {AF_INET, htons(PORT)};

  int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(s == -1){
    perror("socket() failed: ");
  }
  inet_aton("255.255.255.255", &saddr_server.sin_addr);
  unsigned hlp = 1;
  if(setsockopt(s, SOL_SOCKET, SO_BROADCAST, &hlp, sizeof(hlp)) < 0){
    perror("setsockopt broadcast failed: ");
  }
  unsigned short id = 0;
  while(1){
    struct sockaddr_in saddr_server_ = saddr_server;
    unsigned int slen = sizeof(saddr_server);
    struct proto data_req;
    struct proto data_res;

    data_req.id = id++;

    fgets(data_req.buf, sizeof(data_req.buf), stdin);
    data_req.buf[strlen(data_req.buf)-1] = '\0';

    while(1){
        int ret = sendto(s, &data_req, sizeof(data_req), 0, (struct sockaddr*) &saddr_server_, slen);
        if(ret == -1){
          perror("sendto() failed: ");
        }

        ret = recvfrom(s, &data_res, sizeof(data_res), 0, (struct sockaddr*) &saddr_server_, &slen);
        if(ret == -1){
          perror("recvfrom() failed: ");
        }

        if(data_res.id == data_req.id)
            break;
        else
            printf("\tGot message with wrong id, ignoring...\n");
    }

    printf(data_res.flag  ? "YES\n" : "NO\n");
  }
  close(s);
  return 0;
}
