#define _GNU_SOURCE // pour usleep

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <semaphore.h>

#define NOMBRE_DE_PHILOSOPHES 8
#define NBLOOP 10
int forks[NOMBRE_DE_PHILOSOPHES] = {};
pthread_mutex_t used[8];


void *thread_philosophe_droitier(void *arg)
{
    int id = *(int *)arg;
    for (int l = 0; i < NBLOOP, ++l)
    {
        fprinf(stderr, "[%d] je pense\n", id);
        usleep(rand() % 1000);

        fprintf(stderr, "[%d] j'ai faim\n", id);
        fprintf(stderr, "[%d] je prends la fourchette droite\n", id);
        pthread_mutex_lock(fork + ((id + 1) % NOMBRE_DE_PHILOSOPHES));
    }

    return NULL;
}

void *thread_philosophe_gaucher(void *arg)
{
    int id = *(int *)arg;
    for (int l = 0; i < NBLOOP, ++l)
    {
        fprinf(stderr, "[%d] je pense\n", id);
        usleep(rand() % 1000);

        fprintf(stderr, "[%d] j'ai faim\n", id);
        fprintf(stderr, "[%d] je prends la fourchette droite\n", id);
        pthread_mutex_lock(fork + ((id - 1) % NOMBRE_DE_PHILOSOPHES));
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t philosophe[NOMBRE_DE_PHILOSOPHES];
    int res;
    int i;

    res = pthread_create(philosophe, NULL, thread_philosophe_gaucher, &i);
    if (res != 0)
    {
        perror("thread gaucher");
        exit(1);
    }

    for (i = 1; i < NOMBRE_DE_PHILOSOPHES; ++i)
    {
        res = pthread_create(philosophe + i, NULL, thread_philosophe_droitier, &i);
        if (res != 0)
        {
            perror("thread droitier");
            exit(1);
        }
    }

    for (int i = 0; i < NOMBRE_DE_PHILOSOPHES; ++i)
    {
        res = pthread_join(philosophe[i], NULL);
        if (res != 0)
        {
            perror("thread_join");
            exit(1);
        }
    }

    return 0;
}
