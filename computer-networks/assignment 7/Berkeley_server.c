#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#define serv_port 6000

int main(int argc, char *argv[]) 
{
    int sockfd, newsockfd;
    int clilen;
    struct sockaddr_in cli_addr, serv_addr;
    int i;
    char buf[100];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (argc > 1)
    { // Check if argv[1] exists
        serv_addr.sin_port = htons(atoi(argv[1]));
    }
    else
    {
        serv_addr.sin_port = htons(serv_port); 
    }

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Unable to bind local address");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);

    while (1)
    {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("Accept error");
            exit(EXIT_FAILURE);
        }

        if (fork() == 0)
        {
            close(sockfd);
            memset(buf, 0, sizeof(buf)); 
            strcpy(buf, "\nMessage from server: yes, I am ready");
            send(newsockfd, buf, strlen(buf), 0);
            memset(buf, 0, sizeof(buf));              
            recv(newsockfd, buf, sizeof(buf) - 1, 0);
            printf("%s\n", buf);
            close(newsockfd);
            exit(EXIT_SUCCESS);
        }
        close(newsockfd);
    }
}