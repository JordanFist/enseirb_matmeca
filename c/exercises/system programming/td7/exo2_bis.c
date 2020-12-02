#define _GNU_SOURCE // pour usleep

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <semaphore.h>

#define SIZE 1000000
#define NBLOOP 10
int tab[SIZE];
sem_t sem_case_pleine;
sem_t sem_case_vide;

void *thread_reader(void *arg)
{
    //struct mythread_s *myparam = (struct mythread_s *)arg;
    int res;
    for (int j = 0; j < NBLOOP; j++)
    {
        res = 0;
        for (int i = 0; i < SIZE; ++i)
        {
            sem_wait(&sem_case_pleine);
            res += tab[i];
            sem_post(&sem_case_vide);
            if (i % 100)
                sched_yield();
        }
        printf("j'ai scanné tout le stock %d\n", res);
        usleep(100);
    }
    return NULL;
}

void *thread_writer(void *arg)
{
    for (int j = 0; j < NBLOOP; ++j)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            sem_wait(&sem_case_vide);
            tab[i]++;
            sem_post(&sem_case_pleine);
            //sched_yield();
        }
        printf("j'ai rempli les stocks\n");
        usleep(100); //100 microsecondes
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t reader[1], writer[1];
    int res;
    sem_init(&sem_case_pleine, 0, 0); // 0 cells pleine au demarage
    sem_init(&sem_case_pleine, 0, SIZE);

    res = pthread_create(reader, NULL, thread_reader, NULL);
    if (res != 0)
    {
        perror("thread reader");
        exit(1);
    }

    res = pthread_create(writer, NULL, thread_writer, NULL);
    if (res != 0)
    {
        perror("thread writer");
        exit(1);
    }

    res = pthread_join(reader[0], NULL);
    if (res != 0)
    {
        perror("thread join reader");
        exit(1);
    }

    res = pthread_join(writer[0], NULL);
    if (res != 0)
    {
        perror("thread join writer");
        exit(1);
    }

    sem_destroy(&sem_case_pleine);
    sem_destroy(&sem_case_vide);

    return 0;
}
