#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h>

#define SIZE 32768

int main(int argc, char const *argv[])
{
    char *input = "je suis dans le pipe";
    char *output[SIZE];
    int pipefd[2];
    int res = pipe(pipefd);
    if (res == -1) {
        perror("pipe");
        exit(1);
    }
    fcntl(pipefd[0], F_SETPIPE_SZ, 1048576); //change la taille du pipe
    while(1) {
        write(pipefd[1], input, strlen(input));
        read(pipefd [0], output, strlen(input));
        //write(1, output, strlen(input));
        //write(1, "\n", 1);
    }
    return 0;
}
