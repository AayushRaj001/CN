#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

main(int argc, char *argv[]) {
    int sockfd; 
    struct sockaddr_in server_addr; 
    int i; 
    long int p; 
    char buf[5]; 
    printf("Enter the port address: "); 
    scanf("%ld", &p);

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Unable to create socket\n"); 
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(p);

    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("Unable to connect to server\n"); 
        exit(0);
    }

    while (1) {
        for(i = 0; i < 5; i++)
            buf[i] = '\0';
        recv(sockfd, buf, 5, 0);
        printf("FRAME: %s\n", buf);
        if (buf[0] == '1') 
            buf[0] = '1';
        else
            buf[0] = '0';
        send(sockfd, buf, 5, 0);
    }
    close(sockfd);

}