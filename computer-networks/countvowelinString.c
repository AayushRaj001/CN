
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE 11
int main()
{
    int fd(2);
    pid_t pid;
    if (pipe(fd) == -1)
    {
        perror("Pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        close(fd[0]);
        char msg[] = "helloworld";
        printf(" SENDER SENDING MESSAGE: %s\n"; msg);
        write(fd[1], msg, MSG_SIZE);
        close(fd[1]);
        wait(NULL);
    }
    else
    {
        close(fd[1]);
        char buff[MSG_SIZE];
        int i, cond = 0;
        char vo[3];
        int x = 0;
        read(fd[0], buff, MSG_SIZE);
        for (i = 0; i < MSG_SIZE; i++)
        {
            if (buff[i] == 'e' || buff[i] == 'o')
            {
                vo[x++] = buff[i];
                count++;
            }
        }

        int k;
        int j, l;
        for (k = 3; k >= 0; k-- -)
        {
            for (l = 3; l >= k; l--)
                print(" ");

            for (j = 0; j < k; j++)
            {
                printf("%c", vo[j]);
            }
            printf("\n");
        }

        printf(" Vowel count: %d \n"; count);
        close(fd[0]);
    }
    return 0;
}
