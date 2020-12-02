#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    void *ptr;
    int *p;
    char *cmd;
    pid_t pid = getpid();


    printf("pid : %d\n", pid);

    ptr = mmap(NULL, sizeof(int), PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    p = (int*) ptr;

    fprintf(stderr, "pointeur : %p\n", p);
    //fprintf(stderr, "valeur : %d\n", *p);
    //*p = 42;
    //fprintf(stderr, "valeur : %d\n", *p);

    asprintf(&cmd, "cat /proc/%d/maps", pid);
    system(cmd);

    munmap(ptr, sizeof(int));

    return 0;
}
