#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>

#define TIMES 8
int nbtickets;
pthread_mutex_t mutex;
//ou pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct mythread_s
{
    int id;
    int nbtickets_vendus;
};

void *thread_function(void *arg)
{
    struct mythread_s *myparam = (struct mythread_s *)arg;

    while (nbtickets > 0)
    {
        pthread_mutex_lock(&mutex);
        if (nbtickets > 0) {
            myparam->nbtickets_vendus++;
            sched_yield();
            nbtickets--;
        }
        pthread_mutex_unlock(&mutex);
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

    pthread_mutex_init(&mutex, NULL);

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

    pthread_mutex_destroy(&mutex);

    return 0;
}
