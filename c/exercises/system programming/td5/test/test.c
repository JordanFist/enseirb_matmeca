#include <signal.h>
#include <sys/mman.h>
#include <stdio.h>

void handler(int signum) {
    mmap(NULL, 10 * sizeof(int), MAP_SHARED)
}

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, handler);
    pause();

    return 0;
}
