#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
main()
{
    int sockfd, newsockfd;
    int clilen;
    struct sockaddr_in cli_addr, serv_addr;
    int i, J = 0;
    long int p;
    char buf[5];
    char s[8] = {'0', '1', '2', '3', '0', '1', '2', '3'};
    int sf = 0, sl = 2;
    printf("Enter the port address:");
    scanf("%ld", &p);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf(" Error creation in socket!\n");
        exit(0);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(p);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Error in binding\n");
        exit(0);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,
                       &clilen);
    if (newsockfd < 0)
    {
        printf("Accept error\n");
        exit(0);
    }
    while (1)
    {

        for (i = 0; i < 5; i++)
            buf[i] = '\0';
        buf[0] = s[sf];
        send(newsockfd, buf, 5, 0);

        for (i = 0; i < 5; i++)
            buf[i] = '\0';
        recv(newsockfd, buf, 5, 0);
        printf("ACK:%s\n", buf);
        while (s[sf] != buf[0])
        {
            sf++;
            sl++;
        }
        if (sf == 8)
        {
            break;
        }
    }

    close(newsockfd);
    close(sockfd);
}