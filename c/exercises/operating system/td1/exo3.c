#include <unistd.h>
#include <asm/unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <sched.h>

// question 3.c (n'est pas en commentaire)

int main(int argc, char const *argv[])
{
    unsigned long microseconds;
    struct timeval tv, tv1, tv2;
    while (1)
    {
        gettimeofday(&tv1, NULL);
        for (int i = 0; i < 100000; ++i)
        {
            //syscall(__NR_gettimeofday, &tv, NULL);
            //gettimeofday(&tv, NULL);
            sched_yield();
        }
        gettimeofday(&tv2, NULL);
        microseconds = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
        printf("temps : %f µs\n", (float)microseconds / 100001);
    }
    return 0;
}
