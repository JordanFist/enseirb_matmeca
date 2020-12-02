#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


#define SIZE 128

void *ptr;

void handler(int signum)
{
    fprintf(stderr, "%d I receive the signal %d\nthe message sent is : %s",getpid(),  signum, (char*)ptr);
}

int main(int argc, char *argv[])
{
    struct sigaction sa;
    pid_t pid = getpid();
    printf("pid : %d\n", pid);

    int fd;
    
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
    /*
    while(1) {
        fprintf(stderr, "\r%d", fd);
        ((char*)ptr)[fd] = 'a';
        fd++;
    }
    */
    *((pid_t*)ptr) = getpid();
    
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sigaction(SIGUSR1, &sa, NULL);

    sigset_t set;
    sigfillset(&set);
    sigdelset(&set, SIGUSR1);

    sigsuspend(&set);

    munmap(ptr, SIZE);

    return 0;
}
