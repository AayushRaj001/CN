#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void reverse_string(char *str)
{
        int len = strlen(str);
        for (int i = 0; i < len / 2; i++)
        {
                char temp = str[i];
                str[i] = str[len - i - 1];
                str[len - i - 1] = temp;
        }
}

int main()
{
        int pipe_fd[2];
        if (pipe(pipe_fd) == -1)
        {
                perror("Pipe creation failed");
                exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == -1)
        {
                perror("Fork failed");
                exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
                close(pipe_fd[1]);    
                char received_str[6]; 
                if (read(pipe_fd[0], received_str, sizeof(received_str) - 1) == -1)
                {
                        perror("Read failed");
                        exit(EXIT_FAILURE);
                }
                received_str[5] = '\0'; 
                close(pipe_fd[0]);


                reverse_string(received_str);

                printf("Reversed string: %s\n", received_str);
        }
        else
        {

                close(pipe_fd[0]); 
                const char original_str[] = "olleh";
                if (write(pipe_fd[1], original_str, sizeof(original_str) - 1) == -1)
                {
                        perror("Write failed");
                        exit(EXIT_FAILURE);
                }
                close(pipe_fd[1]);
                wait(NULL); 
        }
        return 0;
}