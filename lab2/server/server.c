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
int inet_aton(const char *cp, struct in_addr *inp);

struct proto{
    unsigned short id;
    short flag;
    char buf[BUFLEN];
};

void die(char *s){
    perror(s);
    exit(1);
}

int ispolindrom(char *str){
  int str_len = strlen(str);
  for (int i = 0; i < str_len; ++i){
    if (str[i] != str[str_len-1]){
      return 0;
    }
    str_len--;
  }
  return 1;
}

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
  struct sockaddr_in saddr_client;
  bind(s, (const struct sockaddr*) &saddr_server, sizeof(saddr_server));

  while(1){
      printf("Waiting for data...");
      unsigned int slen = sizeof(saddr_server);
      struct proto data_req;

      int ret = recvfrom(s, &data_req, sizeof(data_req), 0, (struct sockaddr*) &saddr_client, &slen);
      if(ret == -1) printf("recvfrom() failed: ");
      printf("Received Data: %s\n", data_req.buf);

      data_req.flag = ispolindrom(data_req.buf);
      printf(data_req.flag ? "YES\n" : "NO\n");

      ret = sendto(s, &data_req, sizeof(data_req), 0, (struct sockaddr*) &saddr_client, slen);
      if(ret == -1){
        printf("sendto() failed: ");
      }
  }

  close(s);
  return 0;
}
