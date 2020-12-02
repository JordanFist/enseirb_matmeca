#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <semaphore.h>

#define TIMES 8
int nbtickets;
sem_t semaphore;

struct mythread_s
{
    int id;
    int nbtickets_vendus;
};

void *thread_function(void *arg)
{
    struct mythread_s *myparam = (struct mythread_s *)arg;

    while (sem_trywait(&semaphore) == 0)
    {
        myparam->nbtickets_vendus++;
        sched_yield();
        //nbtickets--;
    }

    printf("[%d]j'ai vendu %d tickets\n\n", myparam->id, myparam->nbtickets_vendus);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t threads[TIMES];
    int res;
    int i;
    struct mythread_s params[TIMES];

    if (argc != 2)
        nbtickets = 10000;
    else
        nbtickets = atoi(argv[1]);

    sem_init(&semaphore, 0, nbtickets);

    for (i = 0; i < TIMES; ++i)
    {
        params[i].id = i;
        params[i].nbtickets_vendus = 0;
        res = pthread_create(threads + i, NULL, thread_function, params + i);
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

    int nombre_tickets_vendus = 0;
    for (i = 0; i < TIMES; ++i)
    {
        nombre_tickets_vendus += params[i].nbtickets_vendus;
    }

    printf("On a vendu %d tickets", nombre_tickets_vendus);

    sem_destroy(&semaphore);

    return 0;
}
