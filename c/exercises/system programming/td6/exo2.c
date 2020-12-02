#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>

#define TIMES 8
int global_i = 0;

void *thread_function(void *arg)
{
    int local_i = 0;
    int i = (intptr_t)arg;
    printf("thread :%d, pid : %d\n", i, getpid());
    //printf("global_i(%p) = %d, local_i(%p) = %d\n\n", &global_i, global_i, &local_i, local_i);
    global_i++;
    local_i++;
    return NULL;
    //ou phread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[TIMES];
    int res;
    int i;
    for (i = 0; i < TIMES; ++i)
    {
        res = pthread_create(threads + i, NULL, thread_function, (void*)(intptr_t)i);
        if (res != 0)
        {
            perror("thread_create");
            exit(1);
        }
    }

    for (int i = 0; i < TIMES; ++i)
    {
        res = pthread_join(threads[i], NULL);
        if (res != 0)
        {
            perror("thread_join");
            exit(1);
        }
    }

    return 0;
}
