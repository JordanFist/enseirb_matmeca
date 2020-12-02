#include <unistd.h> 
#include <stdio.h>
#include <sys/time.h>
#include <asm/unistd.h>
#include <sched.h>

int main(int argc, char const *argv[])
{
    unsigned long t;
    struct timeval  tv1, tv2, tv3;
    gettimeofday(&tv1, NULL);
    //gettimeofday(&tv3, NULL);
    //getpid();
    //syscall(__NR_getpid);
    for (int i = 0; i < 100000; ++i) {
        sched_yield(); //passer a un autre processus
    }
    gettimeofday(&tv2, NULL);
    t = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
    printf("\nt = %lu\n", t);
    return 0;
}
