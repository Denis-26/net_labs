#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h> //close()
#include <string.h>

#define BUFLEN 512
#define PORT 8888

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

int main(void){
    struct sockaddr_in si_me, si_other;

    int s, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];

    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1){
        die("bind");
    }

    while(1){
        printf("Waiting for data...");
        fflush(stdout);
        memset(buf,'\0', BUFLEN);

        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1){
            die("recvfrom()");
        }


        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf);

        int polindrom = ispolindrom(buf);

        if (sendto(s, &polindrom, 1, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
    }

    close(s);
    return 0;
}
