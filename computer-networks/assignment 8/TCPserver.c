#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define MAXLINE 20
#define SERVER_PORT 8080

main(int argc, char *argv) {
    int i, j; 
    ssize_t n;
    char line[MAXLINE], recvline[MAXLINE];
    int listenfd, connfd, clilen; 
    struct sockaddr_in servaddr, cliaddr;
    
    
    // Initiate the socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(SERVER_PORT);

    // Bind the socket
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, 1);

    for(;;) {
        
        // Accept the connection
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
        printf("\nConnected to client");
        
        
        while (1) {
            // Read the data from the client
            if ((n = read(connfd, line, MAXLINE)) == 0)
                break;

            // Reverse the data and send it back to the client
            printf("\nLine received: %s", line);
                line[n - 1] = '\0'; 
            j = 0;
            
            for ( i = n - 2; i >= 0; i--)
                recvline[j++] = line[i];
            recvline[j] = '\0';
            write(connfd, recvline, n);
        }
    }
}