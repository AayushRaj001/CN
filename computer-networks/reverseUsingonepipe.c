#include <stdlib.h>
#include <unistd.h>
#include <sys wait.h>

int main()
{
    ind pipe_fd[2];
if (pipe(pipe_fd == - 1 )
{
        perror(" pipe creation failed");
        exit(EXIT_FAILURE);
}

pid_t pid = fork();
if (pid == -1)
{
        perror("Fork failed ");
        exit(EXIT_FAILURE);
}
if (pid == 0)
{
        close(pipe_fd[1]);
        char reversed_str(6);
        read(pipe_fd[0], reversed_str, sizeof(reversed - str));
        close(pipe_fd[0]);
        printf("Reversed string : %s \n", reversed_str);
}
else
{
        close(pipe_fd[0]);
        const char original_str[] = "olleh";
        write(pipe_fd[1], original_str, sizeof(original_str));
        close(pipe_fd[1]);
        wait(NULL);
}
return 0;
}
