#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define SIZE 128

void handler(int signum)
{
    fprintf(stderr, "%d I receive", signum);
}

int main(int argc, char *argv[])
{
    pid_t pid = getpid();
    printf("pid : %d\n", pid);

    int fd;
    void *ptr;

    fd = open("fichier128.txt", O_RDWR);
    if (fd == -1) {
        perror("failed to open");
        exit(1);
    }

    ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED) {
        perror("failed to mmap");
        exit(1);
    }

    close(fd);

    pid = *((pid_t*)ptr); // pid du processus receveur
    strcpy((char*)ptr, "salut\n");

    kill(pid, SIGUSR1);

    munmap(ptr, SIZE);

    return 0;
}
