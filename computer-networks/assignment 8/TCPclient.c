// Design TCP iterative client and
// server application to reverse the
// given input sentence.

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define MAXLINE 20
#define SERVER_PORT 8080

main(int argc, char *argv)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    int sockfd;
    struct sockaddr_in servaddr;

    // Initiate the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(SERVER_PORT);

    // Connect to the server
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("\nEnter the data to be send: ");

    // Send the data to the server
    // and print the response from the server.
    while (fgets(sendline, MAXLINE, stdin) != NULL)
    {
        write(sockfd, sendline, strlen(sendline));
        printf("\nLine Send");
        read(sockfd, recvline, MAXLINE);
        printf("\nReverse of the given sentence is: %s", recvline);
        printf("\n");
    }
    exit(0);
}