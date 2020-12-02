#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char *cmd;

void recursive() {
    static int i = 1;
    char t[65536]
    printf("\ni = %d\n\n", i);
    system(cmd);
    recursive();
}

int main(int argc, char const *argv[])
{
    stack_t ss;
    void *ptr;
    ptr = malloc(SIGSTKSZ);
    ss.ss_sp=ptr;
    ss.ss_flags=0;
    ss.ss_size=SIGSTKSZ;
    sigalstack(&ss, NULL);

    struct sigaction act;
    act.sa_handler = affiche_maps;


    asprintf(&cmd, "cat /proc/%d/maps", getpid());
    recursive();
    return 0;
}
