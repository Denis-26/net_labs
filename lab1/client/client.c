#include<stdio.h> //printf
#include<string.h> //memse
#include<stdlib.h> //exit(0);
#include <unistd.h> //close()
#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "192.168.43.111"
#define BUFLEN 512
#define PORT 4000

void die(char *s){
    perror(s);
    exit(1);
}


int main(void){
    struct sockaddr_in si_other;
    int s, slen=sizeof(si_other);
    char message[BUFLEN];

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0){
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    while(1){
        printf("Enter word : ");
        scanf("%s", message);

        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1){
            die("sendto()");
        }

        int server_answer = 0;
        if (recvfrom(s, &server_answer, 1, 0, (struct sockaddr *) &si_other, &slen) == -1){
            die("recvfrom()");
        }

        if (server_answer){
          printf("%s is %s\n", message, "polindrom");
        } else {
          printf("%s is not %s\n", message, "polindrom");
        }
    }
    close(s);
    return 0;
}
